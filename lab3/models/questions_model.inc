<?php
include_once 'models/db.inc';

/**
 * Retrieve question with specific ID
 */
function retrieveQuestionById($id)
{
	global $db;
	
	$sql = "SELECT * FROM Questions WHERE QuestionID = :id";
    $statement = $db -> prepare($sql);
    $statement -> bindParam(':id', $id);
    $statement -> execute();
    return $statement -> fetch(PDO::FETCH_ASSOC);
}

function retrieveQuestionsByUserId($id) 
{
	global $db;
	
	$sql = "SELECT * FROM Questions WHERE UserID = :id ORDER BY Date DESC";
	
	$statement = $db -> prepare($sql);
	$statement -> bindParam(':id', $id);
	$statement -> execute();
	
	return $statement -> fetchAll(PDO::FETCH_ASSOC);	
}

/**
 * Retrieve 5 most recent questions
 */
function retrieveRecentQuestions()
{
	global $db;
	
	$sql = 'SELECT * FROM Questions ORDER BY Date DESC LIMIT 5';
	$statement = $db -> prepare($sql);
	$statement -> execute();
	return $statement -> fetchAll(PDO::FETCH_ASSOC);
}

/**
 * Insert new question into DB
 */
function insertQuestion($date, $title, $content, $tags, $userId)
{
	global $db;
	
	$sql = "INSERT INTO Questions (Date, Title, Content, Tags, UserID) 
			VALUES (:date, :title, :content, :tags, :userid)";
	
	$statement = $db -> prepare($sql);
    $statement -> bindParam(':date', $date);
	$statement -> bindParam(':title', $title);
	$statement -> bindParam(':content', $content);
	$statement -> bindParam(':tags', $tags);
	$statement -> bindParam(':userid', $userId);
	
	$statement -> execute();
	
	// Return the ID of the added question 
    return $db -> lastInsertId();
}

/**
 * Delete question from DB
 */
function deleteQuestionById($id)
{
    global $db;

    $sql = "DELETE FROM Questions WHERE QuestionID = :id";
    $statement = $db -> prepare($sql);
    $statement -> bindParam(':id', $id);
    $statement -> execute();
}

/**
 * Update a specific question in the DB
 */
function updateQuestion($id, $title, $content, $tags)
{
	global $db;
		
	$sql = "UPDATE Questions SET Title = :title, Content = :content, Tags = :tags WHERE QuestionID = :id";
	$statement = $db -> prepare($sql);
	$statement -> bindParam(':title', $title);
	$statement -> bindParam(':content', $content);
	$statement -> bindParam(':tags', $tags);
    $statement -> bindParam(':id', $id);
    $statement -> execute();
}

function deleteQuestionByUserId($id)
{
	global $db;
	
	$sql = "DELETE FROM Questions WHERE UserID = :id";
	$statement = $db -> prepare($sql);
	$statement -> bindParam(':id', $id);
	$statement -> execute();
}
