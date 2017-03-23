<?php

include_once "include/util.inc";
//include_once "models/users_model.inc";
include_once 'models/User.inc';

//include_once "models/questions_model.inc";
include_once 'models/Question.inc';

/**
 * Show recent questions as home page. 
 */
function get_questions($params) {
    // Get question data
    $data = Question::retrieveRecentQuestions();

    renderTemplate(
        "views/recent_questions_view.inc", 
        array(
            'title' => 'A Questions & Answers Forum',
            'subtitle' => 'Recent Questions',
            'data' => $data
        )
    );
}

/**
 * Opens single full question view
 */
function get_view_question($params) {
    // Get ID as safe param (die if ID not found)
    $id = safeParam($params, 0, false);
    if ($id === false) {
        die("Error: No question selected.");
    }

    // Retrieve question by ID (die if not found)
    $question = Question::retrieveQuestionById($id);
    if (!$question) {
        die("Question not found.");
    }

    // Flag for author edit/delete controls
    $isAuthor = (isLoggedIn() && $_SESSION['UserID'] == $question->getUserId());

    renderTemplate(
        "views/view_question_view.inc", 
        array(
            'title' => $question->getTitle(),
            'question' => $question,
            'isAuthor' => $isAuthor
        )
    );
}

/**
 * Get the post new question view
 */
function get_post_question($params) {
    // Make sure user is logged in
    ensureLoggedIn();

    renderTemplate(
            "views/post_question_view.inc", 
            array(
                'title' => 'Create a new question'
            )
    );
}

/**
 * Add new question to the DB. Make sure required fields are present,
 * if they are missing add errors and render post question view again.
 */
function post_add_question($params) {
    ensureLoggedIn();
    
    // Gather POST data
    $inputs['title'] = safeParam($_POST, 'title', false);
    $inputs['content'] = safeParam($_POST, 'content', false);
    $inputs['tags'] = safeParam($_POST, 'tags', false);
    
    $errors = validate_present(array('title', 'content'));
    // If errors exist, required input is missing. Re-render the create a new question view.
    // Send errors and any input that was already entered
    if ($errors) {
        // @formatter:off
        renderTemplate(
            "views/post_question_view.inc", 
            array(
                'title' => 'Create a new question',
                'errors' => $errors,
                'inputs' => $inputs
            )
        );
        // @formatter:on
        die; // If errors found, stop here
    }

    // No errors found, add question to DB
    /* Get question post input
    $title = safeParam($_POST, 'title', false);
    $content = safeParam($_POST, 'content', false);
    $tags = safeParam($_POST, 'tags', false);
    
     */
    $userId = safeParam($_SESSION, 'UserID', false);
    
    // Set timezone and get current date/time
    date_default_timezone_set('America/New_York');
    $date = date("Y-m-d H:i:s");

    // Insert into DB and get the newly created ID for redirect
    //$id = insertQuestion($date, $title, $content, $tags, $userId);
    
    $question = new Question(null, $date, $inputs['title'], $inputs['content'], $inputs['tags'], $userId);
    $id = $question->insertQuestion();
    
    redirectRelative("questions/view_question/$id");
}

/**
 * Delete a question from the DB. Rediect to recent questions homepage.
 */
function get_delete_question($params) {
    // _GET question ID as safe param
    $id = safeParam($params, 0, false);

    // Get question data from DB to find author's UserID
    $question = Question::retrieveQuestionById($id);

    if (!$question) {
        die("Error: Can't delete question. No question selected. <br /> <a href='" . relativeUrl("questions/questions") . "'>Home</a>");
    }

    // Delete ONLY if the logged in user is the owner of the question
    ensureLoggedInUserIs($question->getUserId());
    if (isLoggedIn() && $_SESSION['UserID'] == $question->getUserId()) {
        $question->deleteQuestion();
    }

    redirectRelative("questions/questions");
}

/**
 * Get edit view for existing question
 */
function get_edit_question($params) {
    ensureLoggedIn();

    $id = safeParam($params, 0, false);
    if ($id === false) {
        die("Error: No question selected.");
    }

    // Retrieve question by ID (die if not found)
    $question = Question::retrieveQuestionById($id);
    if (!$question) {
        die("Error: Question not found.");
    }
    
    // Make sure the user is the owner (block URL fishing edits from non-owners)
    if (isLoggedIn() && $_SESSION['UserID'] == $question->getUserId()) {
        renderTemplate(
            "views/edit_question_view.inc", 
            array(
                'title' => 'Edit your question',
                'question' => $question
            )
        );
    } 
    else {
        // User not owner, send em home
        redirectRelative("index");
    }
}

/**
 * Update question in the DB. Check for required fields, if missing
 * render the edit question view again and show errors.
 */
function post_edit_question($params) {
    // Gather any existing inputs to send back
    $inputs['Title'] = safeParam($_POST, 'title', false);
    $inputs['Content'] = safeParam($_POST, 'content', false);
    $inputs['Tags'] = safeParam($_POST, 'tags', false);
    $inputs['QuestionID'] = safeParam($_POST, 'id', false);
    
    $errors = validate_present(array('title', 'content'));
    // If errors exist, required input is missing. Re-render the create a new question view.
    // Send errors and any input that was already entered
    if ($errors) {
        $tempQuestion = new Question($inputs['QuestionID'], null, $inputs['Title'], $inputs['Content'], $inputs['Tags'], null);
        // @formatter:off
        renderTemplate(
            "views/edit_question_view.inc", 
            array(
                'title' => 'Edit your question',
                'errors' => $errors,
                'question' => $tempQuestion
            )
        );
        // @formatter:on
        die; // If errors found, stop here
    }
    
    // No errors - get question & check question author from database
    $question = Question::retrieveQuestionById($inputs['QuestionID']);
    if (!question) {
        die('No question found.');
    }
    
    ensureLoggedInUserIs($question->getUserId());
   
    $question->setTitle($inputs['Title']);
    $question->setContent($inputs['Content']);
    $question->setTags($inputs['Tags']);
    $question->updateQuestion();
    
    redirectRelative('questions/view_question/' . $inputs['QuestionID']);
}
