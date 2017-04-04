<?php

include_once 'include/util.inc';
include_once 'models/Validator.inc';
include_once 'models/User.inc';
include_once 'models/Question.inc';
include_once 'models/Answer.inc';
include_once 'include/Authenticator.inc';

function get_view_user($params) {
    // Get userID and retreive user info
    $id = safeParam($params, 0, false);
    $user = User::retrieveUserById($id);
    if (!$user) {
        die("Error: user not found.");
    }

    // Get user's questions
    $questions = Question::retrieveQuestionsByUserId($user->getId());

    // Flag for account owner (show the edit/delete account links)
    $ownsAccount = (isLoggedIn() && $_SESSION['UserID'] == $user->getId());
    
    // @formatter: off
    renderTemplate(
        "views/view_user_view.inc", 
        array(
            'title' => 'View User',
            'user' => $user,
            'questions' => $questions,
            'ownsAccount' => $ownsAccount
        )
    );
    // @formatter: on
}

/*
 *  Display user registration page
 */
function get_register($params) {
    // @formatter: off
    renderTemplate(
        "views/edit_user_view.inc", 
        array(
            'title' => 'Register',
            'form_action' => 'user/register',
            'button_text' => 'Register',
            'user' => new User(null, null, null, null, null)
        )
    );
    // @formatter: on
}

/*
 * Register user into the database (POST registration submit event)
 */
function post_register($params) {
    /*
    // Get post data
    $inputs['FirstName'] = safeParam($_POST, 'first-name', false);
    $inputs['LastName'] = safeParam($_POST, 'last-name', false);
    $inputs['Email'] = safeParam($_POST, 'username', false);
    $inputs['Password'] = safeParam($_POST, 'password', false);

    $validator = new Validator();
    $validator -> required('first-name', $inputs['FirstName'], 'First name required');
    $validator -> required('last-name', $inputs['LastName'], 'Last name required');
    $validator ->email('email', $inputs['Email']);
    // Check email doesn't exist in DB already
    if (User::emailExists($inputs['Email'])) {
        $validator ->addError('email-exists', 'Email address already in use');
    }
    $validator -> password('password', $inputs['Password']);

    // If errors found, gather any data entered by the user and re-render with errors shown
    if ($validator -> hasErrors()) {
        $tempUser = new User(null, $inputs['FirstName'], $inputs['LastName'], $inputs['Email'], $inputs['Password']);
     */
    $errors = validateUserForm();
    if ($errors) {
        // @formatter: off
        renderTemplate(
            "views/edit_user_view.inc", 
            array(
                'title' => 'Register',
                'form_action' => 'user/register',
                'button_text' => 'Register',
                //'errors' => $validator ->getErrors(),
                //'user' => $tempUser
                'errors' => $errors['validator'] -> getErrors(),
                'user' => $errors['user']
            )
        );
        // @formatter: on
        die; // Errors found, stop here after re-render
    }

    $inputs = getUserFormInputs();
    
    // Add user to DB
    $user = new User(null, $inputs['FirstName'], $inputs['LastName'], $inputs['Email'], $inputs['Password']);
    $id = $user->insertUser();
    $user = User::retrieveUserById($id); // Retrieve newly created user object
    
    // Add user to "Users" group
    $group = Group::findByName('Users');
    $group ->addUser($user);
    
    updateSession($user);
    ensureLoggedIn();
    redirectRelative("index");
}

/**
 * Edit existing user information
 */
function get_edit_user($params) {
    $id = safeParam($params, 0, false);
    if (!$id) {
        die("Error. No user selected.");
    }
    
    $user = User::retrieveUserById($id);
    if (!$user) {
        die("Error. User not found.");
    }
    
    if (!Authenticator::instance() -> can('user_edit')) {
        ensureLoggedInUserIs($user->getId());
    }
    
    // @formatter: off
    renderTemplate(
        "views/edit_user_view.inc", 
        array(
            'title' => 'Edit User',
            'form_action' => 'user/edit_user',
            'button_text' => 'Save Changes',
            'user' => $user
        )
    );
    // @formatter: on
}

/**
 * Save edit user changes (edit user form POST submit event)
 */
function post_edit_user($params) {
    /* Get post data
    $inputs['FirstName'] = safeParam($_POST, 'first-name', false);
    $inputs['LastName'] = safeParam($_POST, 'last-name', false);
    $inputs['Email'] = safeParam($_POST, 'username', false);
    $inputs['Password'] = safeParam($_POST, 'password', false);
    $inputs['UserID'] = safeParam($_POST, 'user-id', false);
    
    $validator = new Validator();
    $validator -> required('first-name', $inputs['FirstName'], 'First name required');
    $validator -> required('last-name', $inputs['LastName'], 'Last name required');
    $validator ->email('email', $inputs['Email']);
    // Check email doesn't exist in DB already & isnt owners
    $userEmail = User::emailExists($inputs['Email']);
    if ($userEmail && $userEmail['UserID'] != $inputs['UserID']) {
        $validator ->addError('email-exists', 'Email address already in use');
    }
    $validator -> password('password', $inputs['Password']);
    
    // If errors found, gather any data entered by the user and re-render with errors shown
    if ($validator->hasErrors()) {
        $tempUser = new User($inputs['UserID'], $inputs['FirstName'], $inputs['LastName'], $inputs['Email'], $inputs['Password']);
        
     */
    
    $errors = validateUserForm();
    if ($errors) {
        // @formatter: off
        renderTemplate(
            "views/edit_user_view.inc", 
            array(
                'title' => 'Edit User',
                'form_action' => 'user/edit_user',
                'button_text' => 'Save Changes',
                //'errors' => $validator->getErrors(),
                //'user' => $tempUser
                'errors' => $errors['validator'] -> getErrors(),
                'user' => $errors['user']
            )
        );
        // @formatter: on
        die; // Errors found, stop here after re-render
    }
    
    $inputs = getUserFormInputs();
    
    if (!Authenticator::instance() -> can('user_edit')) {
        ensureLoggedInUserIs($inputs['UserID']);
    }
    
    // Update user information in the DB
    $user = User::retrieveUserById($inputs['UserID']);
    $user->setFirstName($inputs['FirstName']);
    $user->setLastName($inputs['LastName']);
    $user->setEmail($inputs['Email']);
    $user->setPassword($inputs['Password']);
    $user->updateUser();

    // Update session info only if user is modifying their own account
    if ($_SESSION['UserID'] == $user->getId()) {
        updateSession($user);
    }
    
    $id = $user->getId();
    redirectRelative("user/view_user/$id");
}

/**
 * Delete user and all their questions and answers from the database
 */
function get_delete_user($params) {
    $id = safeParam($params, 0, false);

    if (!Authenticator::instance() -> can('user_delete')) {
        ensureLoggedInUserIs($id);
    }
    
    $user = User::retrieveUserById($id);
    Question::deleteQuestionsByUserId($user->getId());
    Answer::deleteAnswersByUserId($user->getId());
    $user->deleteUser();
    
    if ($_SESSION['UserID'] == $id) {
        redirectRelative("logout");
    }
    else {
        redirectRelative("index");
    }
}

function validateUserForm() {
    $inputs = getUserFormInputs();
    
    // Validate POST data
    $validator = new Validator();
    $validator -> required('first-name', $inputs['FirstName'], 'First name required');
    $validator -> required('last-name', $inputs['LastName'], 'Last name required');
    $validator ->email('email', $inputs['Email']);
    // Check email doesn't exist in DB already & isnt owners
    $userEmail = User::emailExists($inputs['Email']);
    if ($userEmail && $userEmail['UserID'] != $inputs['UserID']) {
        $validator ->addError('email-exists', 'Email address already in use');
    }
    $validator -> password('password', $inputs['Password']);
    
    // If errors found, return an array containing validator and user objects for re-render
    if ($validator->hasErrors()) {
        $arr = array();
        $arr['user'] = new User($inputs['UserID'], $inputs['FirstName'], $inputs['LastName'], $inputs['Email'], $inputs['Password']);
        $arr['validator'] = $validator;
        return $arr;
    }
    else {
        return false;
    }
}

function getUserFormInputs() {
    $inputs = array();
    
    $inputs['FirstName'] = safeParam($_POST, 'first-name', null);
    $inputs['LastName'] = safeParam($_POST, 'last-name', null);
    $inputs['Email'] = safeParam($_POST, 'username', null);
    $inputs['Password'] = safeParam($_POST, 'password', null);
    $inputs['UserID'] = safeParam($_POST, 'user-id', null);
    
    return $inputs;
}
