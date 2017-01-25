<?php
include_once 'models/db.inc';

function selectAll()
{
    global $db;

    $sql = 'SELECT * FROM Questions';
    $statement = $db -> prepare($sql);
    $statement -> execute();
    return $statement -> fetchAll(PDO::FETCH_ASSOC);
	// THIS IS FETCH ALL
}

function retrieveQuestionById($id)
{
	global $db;
	
	$sql = "SELECT * FROM Questions WHERE QuestionID = :id";
    $statement = $db -> prepare($sql);
    $statement -> bindParam(':id', $id);
    $statement -> execute();
    return $statement -> fetch(PDO::FETCH_ASSOC);
	// ONLY FETCH!
}

function retrieveRecentQuestions()
{
	global $db;
	
	$sql = 'SELECT * FROM Questions ORDER BY Date DESC LIMIT 5';
	$statement = $db -> prepare($sql);
	$statement -> execute();
	return $statement -> fetchAll(PDO::FETCH_ASSOC);
}
