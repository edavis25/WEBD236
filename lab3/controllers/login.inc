<?php
include_once "include/util.inc";
include_once 'models/User.inc';
include_once 'include/Authenticator.inc';
include_once 'include/Email.inc';
include_once 'include/Logger.inc';


function get_index($params) {
    // @formatter: off
    renderTemplate(
        "views/login_view.inc",
        array(
            'title' => 'Login',
        )
    );
    // @formatter: on
}

function post_index($params) {
    $username = safeParam($_POST, 'username', false);
    $password = safeParam($_POST, 'password', false);
    
    $validUser = User::isValidUser($username, $password);
    if ($validUser) {
        updateSession($validUser);
		
        if (isset($_SESSION['redirect'])) {
            $redirect = $_SESSION['redirect'];
            redirect($redirect);
            exit();
        }
        redirectRelative("index");
    } 
    else {
        // @formatter:off
        renderTemplate(
            "views/login_view.inc",
            array(
                'title' => 'Login',
                'errors' => array("Invalid username/password"),
                'username' => $username,
                'password' => $password
            )
        );
        // @formatter:on
    }
}

function get_forgot_password($params) {
    // Look for validator object sent as param
    if (isset($params[0]) && $params[0] instanceof Validator) {
        $errors = $params[0] -> getErrors();
        foreach ($errors as $key => &$error) {
            $error = safeParam($errors, $key, null);
        }
    }
    else {
        $errors = null;
    }

    // @formatter: off
    renderTemplate(
        "views/forgot_password_view.inc",
        array(
            'title' => "Password Recovery",
            'errors' => $errors
        )
    );
    // @formatter: on
}

function post_forgot_password($params) {
    $address = safeParam($_POST, 'email', false);
    $user = User::retrieveUserByEmail($address);
    
    $validator = new Validator();
    $validator -> email('email', $address);
    $validator -> required('no_user', $user->getEmail(), 'Email address not found.');
    if ($validator -> hasErrors()) {
        get_forgot_password(array($validator));
        die;
    }
    
    // Get users IP (this will be ::1 for localhost)
    $ip = safeParam($_SERVER, 'REMOTE_ADDR', null);
    Logger::instance() -> info("Password recovery requested for account: {$user->getEmail()} from IP: $ip");
    
    // Create email
    $subject = 'Account Recovery';
    $name = User::getFullName($user->getId());
    $recipient = "\"$name\" <{$user->getEmail()}>";

    $email = new Email();
    $email -> setRecipient($recipient);
    $email -> setSubject($subject);
    $email -> setContentType('text/html');
    
    // @formatter:off
    $email -> send(
        'views/forgot_password_email.inc',
        array(
            'title' => $subject,
            'name' => $user -> getFirstName(),
            'password' => $user -> getPassword(),
            'ip' => $ip
        )
    );
    
    // Show email success screen
    renderTemplate(
        'views/forgot_password_sent.inc',
        array(
            'title' => 'Recovery Email Sent',
            'email' => $user->getEmail()
        )
    );
    // @formatter:on
}