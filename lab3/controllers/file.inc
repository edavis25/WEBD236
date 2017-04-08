<?php
include_once "include/util.inc";
include_once 'models/Question.inc';
include_once 'models/Validator.inc';
include_once 'include/Authenticator.inc';
include_once 'include/UploadDir.inc';
include_once 'models/File.inc';

function post_add($params) {
    if (!Authenticator::instance() -> can('question_edit')) {
        ensureLoggedInUserIs($question->getUserId());
    }
    
    $questionId = safeParam($_POST, 'question-id', false);
    $question = Question::retrieveQuestionById($questionId);
    if (!$question) {
        die('Error: No question found.');
    }
    
    $dir = new UploadDir();
    $file = $dir ->getUpload('file');
    
    $file -> setQuestionId($question->getId());
    
    $validator = $file -> validate();
    if ($validator ->hasErrors()) {
        die('Error: Problem with file upload.');
    }
    
    $file -> insert();
    redirectRelative("questions/view_question/{$question->getId()}");
}

function get_view($params) {
    $id = safeParam($params, 0, false);
    $file = File::findById($id);
    if (!$file) {
        die('Error: File not found.');
    }
    
    header('Last-Modified: ' . date('r'));
    header('Accept-Ranges: bytes');
    header('Content-Length: ' . $file -> getSize());
    header('Content-Type: ' . $file -> getType());
    header('Content-Disposition: inline; filename=' . $file -> getOrigName());
    ob_clean();
    flush();
    readfile($file -> fullPath());
    exit;
}
