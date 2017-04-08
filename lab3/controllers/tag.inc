<?php
include_once 'include/util.inc';
include_once 'models/Question.inc';
include_once 'models/User.inc';
include_once 'models/Answer.inc';
include_once 'include/Authenticator.inc';

function get_view_questions($params) {
    $tag = safeParam($params, 0, false);
    $questions = Question::retrieveQuestionsByTagName($tag);
    
    // @formatter: off
    renderTemplate(
        "views/recent_questions_view.inc", 
        array(
            'title' => "Questions tagged: '$tag'",
            'questions' => $questions,
            'newQuestionButtonText' => "[ Post New Question Tagged <i>$tag</i> ]",
            'prefillTag' => $tag
        )
    );
    // @formatter: on
}
