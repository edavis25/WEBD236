<?php
include_once "include/util.inc";
include_once 'models/Question.inc';
include_once 'models/Validator.inc';
include_once 'include/Authenticator.inc';
include_once 'include/UploadDir.inc';
include_once 'models/File.inc';
include_once 'controllers/questions.inc';

function post_add($params) {
    $questionId = safeParam($_POST, 'question-id', false);
    $question = Question::retrieveQuestionById($questionId);
    if (!$question) {
        die('Error: No question found.');
    }
    
    if (!Authenticator::instance() -> can('question_edit')) {
        ensureLoggedInUserIs($question->getUserId());
    }
    
    // Attempt file upload
    $dir = new UploadDir();
    $file = $dir ->getUpload('file');
    if (!$file) {
        $validator = new Validator();
        $validator -> addError('file', 'There was a problem with file upload');
        get_view_question(array($questionId, $validator));
        die;
    }
    
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

function get_download($params) {
    $fileId = safeParam($params, 0);
    $file = File::findById($fileId);
    if (!$file) {
        die('Error: File not found.');
    }
    
    header('Content-Description: File Transfer');
    header('Content-Type: ' . $file -> getType());
    header('Content-Disposition: attachment; filename=' . $file -> getOrigName());
    header('Content-Transfer-Encoding: binary');
    header('Expires: 0');
    header('Cache-Control: must-revalidate');
    header('Pragma: public');
    header('Content-Length: ' . $file -> getSize());
    ob_clean();
    flush();
    readfile($file -> fullPath());
    exit ;
}

function get_delete($params) {
    $fileId = safeParam($params, 0, false);
    $questionId = safeParam($params, 1, false);
    
    $file = File::findById($fileId);
    $question = Question::retrieveQuestionById($questionId);
    if (!$question || !$file) {
        die('File and/or question not found');
    }
    
    if (!Authenticator::instance() -> can('question_edit')) {
        ensureLoggedInUserIs($question->getUserId());
    }
 
    $file -> delete();
    redirectRelative("questions/view_question/{$question->getId()}");
}

function get_clean_orphan_files($params) {
    Authenticator::instance() -> ensure('admin_page');
    
    $uploadDir = new UploadDir();
    $dir = $uploadDir -> getDirectory();
       
    if (is_dir($dir)) {
        $files = scandir($dir);
        $files = array_diff($files, array('.', '..'));
        
        $orphans = array();
        foreach ($files as $file) {
            $tempFile = File::findByDiskName($file);
            if (!$tempFile -> getNameOnDisk()) {
                $orphans[] = $file;
                Logger::instance() -> info("User {$_SESSION['UserID']} removed orphan file: $file from $dir");
                unlink($dir . DIRECTORY_SEPARATOR . $file);
            }
        }
    }
    
    $numberRemoved = sizeof($orphans);
    $orphans = ($orphans) ? $orphans : array('No orphaned files found.');
    
    // @formatter: off
    renderTemplate(
        "views/orphan_files_view.inc",
        array(
            'title' => 'Clean Orphaned Uploads',
            'orphans' => $orphans,
            'directory' => $dir,
            'numberRemoved' => $numberRemoved
        )
    );
    // @formatter: on
}