<?php
include_once "include/util.inc";
include_once "models/questions_model.inc";
include_once "models/users_model.inc";

/**
 * Show recent questions as home page. 
 */
function get_questions($params)
{
	$data = retrieveRecentQuestions();

	renderTemplate(
        "views/recent_questions_view.inc",
        array(
            'title' => 'My Questions & Answers',
            'subtitle' => 'Recent Questions',
            'data' => $data
        )
    );
}

/**
 * Opens single full question view
 */
function get_view_question($params)
{
	// Get ID as safe param (die if ID not found)
	$id = safeParam($params, 0, false);
    if ($id === false) {
        die("Error: No question selected");
    }
	
	// Retrieve question by ID (die if not found)
    $question = retrieveQuestionById($id);
    if (!$question) {
    	die("Question not found.");
    }		

	renderTemplate(
        "views/view_question_view.inc",
        array(
            'title' => $question['Title'],
            'question' => $question
        )
    );
}

/**
 * Get the post new question view
 */
function get_post_question($params)
{
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
function post_add_question($params)
{
	$errors = validate_present(array('title', 'content'));
    // If errors exist, required input is missing. Re-render the create a new question view.
    // Send errors and any input that was already entered
    if ($errors) {
    	// Gather any existing inputs to send
    	$inputs['title'] = safeParam($_POST, 'title', false);
		$inputs['content'] = safeParam($_POST, 'content', false);
		$inputs['tags'] = safeParam($_POST, 'tags', false);
    	renderTemplate(
       		"views/post_question_view.inc",
        	array(
    	        'title' => 'Create a new question',
    	        'errors' => $errors,
    	        'inputs' => $inputs
	        )
   		 );
    	die; // If errors found, stop here
    }
	
	// No errors found, add question to DB
	// Get question post input
	$title = safeParam($_POST, 'title', false);
	$content = safeParam($_POST, 'content', false);
	$tags = safeParam($_POST, 'tags', false);	

	// Set timezone and get current date/time
	date_default_timezone_set('America/New_York');
	$date = date("Y-m-d H:i:s");
	
	// Insert into DB and get the newly created ID for redirect
	$id = insertQuestion($date, $title, $content, $tags);
	redirectRelative("questions/view_question/$id");
}

/**
 * Delete a question from the DB. Rediect to recent questions homepage.
 */
function get_delete_question($params)
{
	$id = safeParam($params, 0, false);
    if ($id === false) {
    	die("Error: Can't delete question. No question selected. <br /> <a href='".relativeUrl("questions/questions")."'>Home</a>");
    }

    deleteQuestionById($id);
	redirectRelative("questions/questions");
}

/**
 * Get edit view for existing question
 */
function get_edit_question($params) 
{
	$id = safeParam($params, 0, false);
	if ($id === false) {
        die("Error: No question selected");
    }
	
	// Retrieve question by ID (die if not found)
    $question = retrieveQuestionById($id);
    if (!$question) {
    	die("Error: Question not found.");
    }
	
	renderTemplate(
        "views/edit_question_view.inc",
        array(
            'title' => 'Edit your question',
            'inputs' => $question
        )
    );
}

/**
 * Update question in the DB. Check for required fields, if missing
 * render the edit question view again and show errors.
 */
function post_edit_question($params)
{
	$errors = validate_present(array('title', 'content'));
    // If errors exist, required input is missing. Re-render the create a new question view.
    // Send errors and any input that was already entered
    if ($errors) {
    	// Gather any existing inputs to send back
    	$inputs['Title'] = safeParam($_POST, 'title', false);
		$inputs['Content'] = safeParam($_POST, 'content', false);
		$inputs['Tags'] = safeParam($_POST, 'tags', false);
		$inputs['QuestionID'] = safeParam($_POST, 'id', false);
    	renderTemplate(
       		"views/edit_question_view.inc",
        	array(
    	        'title' => 'Edit your question',
    	        'errors' => $errors,
    	        'inputs' => $inputs
	        )
   		 );
    	die; // If errors found, stop here
    }
	
	// If no errors found, update question in DB
	$id = safeParam($_POST, 'id', false);
	$title = safeParam($_POST, 'title', false);
	$content = safeParam($_POST, 'content', false);
	$tags = safeParam($_POST, 'tags', false);
	
	updateQuestion($id, $title, $content, $tags);
	redirectRelative("questions/view_question/$id");
}
