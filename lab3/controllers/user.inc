<?php

include_once "include/util.inc";
//include_once "models/users_model.inc";
include_once 'models/User.inc';
include_once "models/Question.inc";

// View user
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

    renderTemplate(
        "views/view_user_view.inc", 
        array(
            'title' => 'View User',
            'user' => $user,
            'questions' => $questions,
            'ownsAccount' => $ownsAccount
        )
    );
}

/*
 *  Display user registration page
 */
function get_register($params) {
    renderTemplate(
        "views/edit_user_view.inc", 
        array(
            'title' => 'Register',
            'form_action' => 'user/register',
            'button_text' => 'Register',
            'user' => new User(null, null, null, null, null)
        )
    );
}

/*
 * Register user into the database (POST registration submit event)
 */

function post_register($params) {
    // Get post data
    $inputs['FirstName'] = safeParam($_POST, 'first-name', false);
    $inputs['LastName'] = safeParam($_POST, 'last-name', false);
    $inputs['Email'] = safeParam($_POST, 'username', false);
    $inputs['Password'] = safeParam($_POST, 'password', false);

    // Check for all required fields and begin building error string (if necessary)
    $errors = validate_present(array('first-name', 'last-name', 'username', 'password'));

    // Check for valid email (doesn't exist in DB already)
    if (User::emailExists($inputs['Email'])) {
        $errors .= '&bull; Email address already in use.';
    }

    // Errors found, gather any data entered by the user and re-render with errors shown
    if ($errors) {
        $tempUser = new User(null, $inputs['FirstName'], $inputs['LastName'], $inputs['Email'], $inputs['Password']);
        renderTemplate(
            "views/edit_user_view.inc", 
            array(
                'title' => 'Register',
                'form_action' => 'user/register',
                'button_text' => 'Register',
                'errors' => $errors,
                'user' => $tempUser
            )
        );
        die; // Errors found, stop here after re-render
    }

    // No errors found: register and log user in
    // Add user to DB
    $user = new User(null, $inputs['FirstName'], $inputs['LastName'], $inputs['Email'], $inputs['Password']);
    $id = $user->insertUser();
    //$id = insertUser($inputs['FirstName'], $inputs['LastName'], $inputs['Email'], $inputs['Password']);

    // Log user in and set SESSION variables
    $_SESSION['loggedin'] = true;
    $_SESSION['UserID'] = $id;
    $_SESSION['FirstName'] = $user->getFirstName();
    $_SESSION['LastName'] = $user->getLastName();
    $_SESSION['Email'] = $user->getEmail();
    
    ensureLoggedIn();
    redirectRelative("index");
}

/**
 * Edit existing user information
 */
function get_edit_user($params) {
    $id = safeParam($params, 0, false);
    
    ensureLoggedInUserIs($id);

    $user = User::retrieveUserById($id);
    if (!$user) {
        die("Error. User not found.");
    }

    renderTemplate(
        "views/edit_user_view.inc", 
        array(
            'title' => 'Edit User',
            'form_action' => 'user/edit_user',
            'button_text' => 'Save Changes',
            'user' => $user
        )
    );
}

/**
 * Save edit user changes (edit user form POST submit event)
 */
function post_edit_user($params) {
    // Get post data
    $inputs['FirstName'] = safeParam($_POST, 'first-name', false);
    $inputs['LastName'] = safeParam($_POST, 'last-name', false);
    $inputs['Email'] = safeParam($_POST, 'username', false);
    $inputs['Password'] = safeParam($_POST, 'password', false);
    $inputs['UserID'] = safeParam($_POST, 'user-id', false);
    
    ensureLoggedInUserIs($inputs['UserID']);

    // Check for all required fields and begin building error string (if necessary)
    $errors = validate_present(array('first-name', 'last-name', 'username', 'password'));

    /*
    // Check for valid email ONLY if the user changed it
    if ($_SESSION['Email'] != $inputs['Email']) {
        if (isValidEmail($inputs['Email'])) {
            $errors .= '&bull; Email address already in use.';
        }
    }
    */
    
    $userEmail = User::emailExists($inputs['Email']);
    if ($userEmail && $userEmail['UserID'] != $inputs['UserID']) {
        $errors .= '&bull; Email address already in use.';
    }

    // Errors found, gather any data entered by the user and re-render with errors shown
    if ($errors) {
        $tempUser = new User($inputs['UserID'], $inputs['FirstName'], $inputs['LastName'], $inputs['Email'], $inputs['Password']);
        renderTemplate(
                "views/edit_user_view.inc", 
                array(
                    'title' => 'Edit User',
                    'form_action' => 'user/edit_user',
                    'button_text' => 'Save Changes',
                    'errors' => $errors,
                    'user' => $tempUser
                )
        );
        die; // Errors found, stop here after re-render
    }

    // Update user information in the DB
    $user = User::retrieveUserById($inputs['UserID']);
    $user->setFirstName($inputs['FirstName']);
    $user->setLastName($inputs['LastName']);
    $user->setEmail($inputs['Email']);
    $user->setPassword($inputs['Password']);
    
    $user->updateUser();

    // Update SESSION variables
    $_SESSION['FirstName'] = $user->getFirstName();
    $_SESSION['LastName'] = $user->getLastName();
    $_SESSION['Email'] = $user->getEmail();
    
    $id = $user->getId();
    redirectRelative("user/view_user/$id");
}

/**
 * Delete user and all their questions from the database
 */
function get_delete_user($params) {
    $id = safeParam($params, 0, false);

    ensureLoggedInUserIs($id);

    $user = User::retrieveUserById($id);
    Question::deleteQuestionsByUserId($user->getId());
    $user->deleteUser();
    
    redirectRelative("logout");
}
