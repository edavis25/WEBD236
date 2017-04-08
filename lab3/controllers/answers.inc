<?php
include_once "include/util.inc";
include_once 'models/User.inc';
include_once 'models/Question.inc';
include_once 'models/Validator.inc';
include_once 'models/Answer.inc';
include_once 'include/Authenticator.inc';

function post_add_answer($params) {
    Authenticator::instance() -> ensure('answer_create');
    
    // Get POST data
    $userId = safeParam($_SESSION, 'UserID', null);
    $questionId = safeParam($_POST, 'question-id', null);
    $content = safeParam($_POST, 'answer-content', null);
    
    $validator = new Validator();
    $validator -> required('content', $content, 'Answer content required');
    $validator -> required('userId', $userId, 'User ID missing');
    $validator -> required('questionId', $questionId, 'Question ID missing');
    if ($validator -> hasErrors()) {
        $question = Question::retrieveQuestionById($questionId);
        if (!$question) {
            die("Question not found.");
        }
        // Get answers
        $answers = Answer::retrieveAnswersByQuestionId($question->getId());
        
        // Flag for author edit/delete controls
        $isAuthor = (isLoggedIn() && $_SESSION['UserID'] == $question->getUserId());
        // @formatter: off
        renderTemplate(
            "views/view_question_view.inc", 
            array(
                'title' => $question->getTitle(),
                'question' => $question,
                'isAuthor' => $isAuthor,
                'errors' => $validator->getErrors(),
                'answers' => $answers
            )
        );
        // @formatter:on
        die; // If errors found, stop here
    }
    
    date_default_timezone_set('America/New_York');
    $date = date("Y-m-d H:i:s");
    $answer = new Answer(null, $userId, $questionId, $date, $content);
    $answer->insertAnswer();
    
    redirectRelative("questions/view_question/$questionId");
}



function get_delete_answer($params) {
    $id = safeParam($params, 0, false);
    
    $answer = Answer::retrieveAnswerById($id);
    if (!$answer) {
        die('Error: No answer found to delete');
    }
    
    if (!Authenticator::instance() -> can('answer_delete')) {
        ensureLoggedInUserIs($answer->getUserId());
    }
    
    $answer->deleteAnswer();
    
    redirectRelative("questions/view_question/{$answer->getQuestionId()}");
}