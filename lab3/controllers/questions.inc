<?php

include_once "include/util.inc";
include_once 'models/User.inc';
include_once 'models/Question.inc';
include_once 'models/Validator.inc';
include_once 'models/Answer.inc';
include_once 'include/Authenticator.inc';
include_once 'models/File.inc';

/**
 * Show recent questions as home page. 
 */
function get_questions($params) {
    // Get question data
    $questions = Question::retrieveRecentQuestions();
    
    // @formatter: off
    renderTemplate(
        "views/recent_questions_view.inc", 
        array(
            'title' => 'A Questions & Answers Forum',
            'subtitle' => 'Recent Questions',
            'questions' => $questions,
            'newQuestionButtonText' => '[Post New Question]'
        )
    );
    // @formatter: on
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
    
    // Get answers & files
    $answers = Answer::retrieveAnswersByQuestionId($question->getId());
    $files = File::findByQuestionID($question->getId());
    
    // Flag for author edit/delete controls
    $isAuthor = ( isLoggedIn() && $_SESSION['UserID'] == $question->getUserId() );
    
    // @formatter: off
    renderTemplate(
        "views/view_question_view.inc", 
        array(
            'title' => $question->getTitle(),
            'question' => $question,
            'isAuthor' => $isAuthor,
            'answers' => $answers,
            'files' => $files
        )
    );
    // @formatter: on
}

/**
 * Get the post new question view
 */
function get_post_question($params) {
    // Make sure user is logged in
    ensureLoggedIn();
    
    // Look for prefilled tag
    $inputs['tags'] = safeParam($params, 0, null);

    // @formatter: off
    renderTemplate(
        "views/post_question_view.inc", 
        array(
            'title' => 'Create a new question',
            'inputs' => $inputs
        )
    );
    // @formatter: on
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
        
    $validator = new Validator();
    $validator -> required('title', $inputs['title'], 'Title missing');
    $validator -> required('content', $inputs['content'], 'Content missing');
    
    // If errors exist, required input missing - re-render the new question view.
    if ($validator->hasErrors()) {
        // @formatter:off
        renderTemplate(
            "views/post_question_view.inc", 
            array(
                'title' => 'Create a new question',
                'errors' => $validator->getErrors(),
                'inputs' => $inputs
            )
        );
        // @formatter:on
        die; // Errors found, stop here
    }

    $userId = safeParam($_SESSION, 'UserID', false);
    
    // Set timezone and get current date/time
    date_default_timezone_set('America/New_York');
    $date = date("Y-m-d H:i:s");

    // Insert into DB and get the newly created ID for redirect    
    $question = new Question(null, $date, trim($inputs['title']), $inputs['content'], trim($inputs['tags']), $userId);
    $id = $question->insertQuestion();
    
    redirectRelative("questions/view_question/$id");
}

/**
 * Delete a question from the DB. Redirect to recent questions home page.
 */
function get_delete_question($params) {
    // _GET question ID as safe param
    $id = safeParam($params, 0, false);

    // Get question data from DB to find author's UserID
    $question = Question::retrieveQuestionById($id);
    if (!$question) {
        die("Error: Can't delete question. No question selected. <br /> <a href='" . relativeUrl("questions/questions") . "'>Home</a>");
    }

    if (!Authenticator::instance() -> can('question_delete')) {
        ensureLoggedInUserIs($question->getUserId());
    }
    
    Answer::deleteAnswersByQuestionId($question->getId());
    $question->deleteQuestion();

    redirectRelative("questions/questions");
}

/**
 * Get edit view for existing question
 */
function get_edit_question($params) {
    $id = safeParam($params, 0, false);
    if ($id === false) {
        die("Error: No question selected.");
    }
    
    $question = Question::retrieveQuestionById($id);
    if (!$question) {
        die("Error: Question not found.");
    }
    
    if (!Authenticator::instance() -> can('question_edit')) {
        ensureLoggedInUserIs($question->getUserId());
    }
    
    renderTemplate(
        "views/edit_question_view.inc", 
        array(
           'title' => 'Edit your question',
           'question' => $question
        )
    );
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
    
    $validator = new Validator();
    $validator -> required('title', $inputs['Title'], 'Title missing');
    $validator -> required('content', $inputs['Content'], 'Content missing');
    
    // If errors exist, required input missing - re-render the new question view.
    if ($validator->hasErrors()) {
        $tempQuestion = new Question($inputs['QuestionID'], null, trim($inputs['Title']), $inputs['Content'], trim($inputs['Tags']), null);
        // @formatter:off
        renderTemplate(
            "views/edit_question_view.inc", 
            array(
                'title' => 'Edit your question',
                'errors' => $validator->getErrors(),
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
    
    if (!Authenticator::instance() -> can('question_edit')) {
        ensureLoggedInUserIs($question->getUserId());
    }
   
    $question->setTitle(trim($inputs['Title']));
    $question->setContent($inputs['Content']);
    $question->setTags(trim($inputs['Tags']));
    $question->updateQuestion();
    
    redirectRelative('questions/view_question/' . $inputs['QuestionID']);
}
