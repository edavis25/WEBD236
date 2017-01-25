<?php
include_once "include/util.inc";
include_once "models/questions_model.inc";

/**
 * Gets recent question home page.
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
    	die("No question with id $id found.");
    }		

// working firefox injection
//http://localhost/Aptana/lab2/questions/view_question/test=<script>alert("test");<%2Fscript>
	
	
	renderTemplate(
        "views/view_question_view.inc",
        array(
            //'title' => 'View Question',
            'title' => $question['Title'],
            'question' => $question
        )
    );
}

/**
 * Get post question view
 */
function get_post_question($params)
{
	
	$data = array();
	
	renderTemplate(
        "views/post_question_view.inc",
        array(
            //'title' => 'View Question',
            'title' => 'Create a new question',
            'data' => $data
        )
    );
}
