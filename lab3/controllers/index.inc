<?php
include_once "include/util.inc";
include_once "controllers/questions.inc";

function get_index($params) {
    // This Handles the /, /index, and /index/index urls.
    // redirect to the questions controller get_question() function...
    get_questions($params);
}