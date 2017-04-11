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

function get_view_question($params) {
    $id = safeParam($params, 0, false);
    if ($id === false) {
        die("Error: No question selected.");
    }
    
    // Look for validator object sent as param when this method called from another controller (namely answers.inc + file.inc)
    if (isset($params[1]) && $params[1] instanceof Validator) {
        $errors = $params[1] -> getErrors();
        foreach ($errors as $key => &$error) {
            $error = safeParam($errors, $key, null);
        }
    }
    else {
        $errors = null;
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
            'files' => $files,
            'errors' => $errors
        )
    );
    // @formatter: on
}

function get_post_question($params) {
    Authenticator::instance() -> ensure('question_create');
    
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

function post_add_question($params) {
    Authenticator::instance() -> ensure('question_create');
    
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

function get_delete_question($params) {
    $id = safeParam($params, 0, false);

    // Get question data from DB to find author's UserID
    $question = Question::retrieveQuestionById($id);
    if (!$question) {
        die("Error: Can't delete question. No question selected. <br /> <a href='" . relativeUrl("questions/questions") . "'>Home</a>");
    }

    if (!Authenticator::instance() -> can('question_delete')) {
        ensureLoggedInUserIs($question->getUserId());
    }
    
    // Delete the question's answers & files
    Answer::deleteAnswersByQuestionId($question->getId());
    $files = File::findByQuestionID($question->getId());
    foreach ($files as $file) {
        $file -> delete();
    }
    
    $question -> deleteQuestion();

    redirectRelative("questions/questions");
}

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

