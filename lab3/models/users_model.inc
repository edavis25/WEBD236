<?php
include_once 'models/db.inc';


function isValidUser($username, $password) {
    //return $username == 'admin' && $password == 'admin';
    global $db;
	$sql = "SELECT * FROM Users WHERE Email = :email AND Password = :password";
	$statement = $db -> prepare($sql);
	$statement -> bindParam(':email', $username);
	$statement -> bindParam(':password', $password);
	$statement -> execute();
	return $statement -> fetch(PDO::FETCH_ASSOC);
}

function isValidEmail($email) {
	global $db;
	$sql = "SELECT * FROM Users WHERE Email = :email";
	$statement = $db -> prepare($sql);
	$statement -> bindParam(':email', $email);
	$statement -> execute();
	return $statement -> fetch(PDO::FETCH_ASSOC);
}

/**
 * Insert new user into DB
 */
function insertUser($first, $last, $email, $password) {
	global $db;
	
	$sql = "INSERT INTO Users (FirstName, LastName, Email, Password) 
			VALUES (:first, :last, :email, :password)";
	
	$statement = $db -> prepare($sql);
    $statement -> bindParam(':first', $first);
	$statement -> bindParam(':last', $last);
	$statement -> bindParam(':email', $email);
	$statement -> bindParam(':password', $password);
	
	$statement -> execute();
	
	// Return the ID of the added question 
    return $db -> lastInsertId();
}

/**
 * Retrieve question with specific ID
 */
function retrieveUserById($id) {
	global $db;
	
	$sql = "SELECT * FROM Users WHERE UserID = :id";
    $statement = $db -> prepare($sql);
    $statement -> bindParam(':id', $id);
    $statement -> execute();
    return $statement -> fetch(PDO::FETCH_ASSOC);
}