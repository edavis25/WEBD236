<?php
include_once 'models/db.inc';

// TODO: This function is simply a test. Change it to search the DB for valid user
function isValidUser($username, $password) {
    return $username == 'admin' && $password == 'admin';
}

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
