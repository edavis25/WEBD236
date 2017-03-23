<?php
require_once 'models/Model.inc';
require_once 'include/util.inc';

class User extends Model {
    
    private $firstName;
    private $lastName;
    private $email;
    private $password;
    
    public function __construct($id, $firstName, $lastName, $email, $password) {
        parent::__construct($id);
        $this->setFirstName($firstName);
        $this->setLastName($lastName);
        $this->setEmail($email);
        $this->setPassword($password);
    }
    
    public function getFirstName() {
        return $this->firstName;
    }
    public function setFirstName($name) {
        $this->firstName = $name;
    }
    
    public function getLastName() {
        return $this->lastName;
    }
    public function setLastName($name) {
        $this->lastName = $name;
    }
    
    public function getFullName() {
        return $this->firstName . " " . $this->lastName;
    }
    
    public function getEmail() {
        return $this->email;
    }
    public function setEmail($email) {
        $this->email = $email;
    }
    
    public function getPassword() {
        return $this->password;
    }
    public function setPassword($pass) {
        $this->password = $pass;
    }
    
    public static function retrieveUserById($id) {
	$db = self::getDb();
	
        $sql = "SELECT * FROM Users WHERE UserID = :id";
        
        $statement = $db -> prepare($sql);
        $statement -> bindParam(':id', $id);
        $statement -> execute();
        
        $row = $statement->fetch(PDO::FETCH_ASSOC);
        return self::makeUserFromRow($row);
    }
    
    public static function isValidUser($username, $password) {
        $db = self::getDb();
        
	$sql = "SELECT * FROM Users WHERE Email = :email AND Password = :password";
        
	$statement = $db -> prepare($sql);
	$statement -> bindParam(':email', $username);
	$statement -> bindParam(':password', $password);
	$statement -> execute();
        
    	$row = $statement -> fetch(PDO::FETCH_ASSOC);
        
        // If user found, send back a user object for session variables
        if ($row) {
            return self::makeUserFromRow($row);
        }
        
        return false;
    }
    
    public static function emailExists($email) {
	$db = self::getDb();
        
	$sql = "SELECT * FROM Users WHERE Email = :email";
        
	$statement = $db -> prepare($sql);
	$statement -> bindParam(':email', $email);
	$statement -> execute();
        
	return $statement -> fetch(PDO::FETCH_ASSOC);
    }
    
    public function insertUser() {
        $db = self::getDb();
	
	$sql = "INSERT INTO Users (FirstName, LastName, Email, Password) 
			VALUES (:first, :last, :email, :password)";
	
	$statement = $db -> prepare($sql);
        $statement -> bindParam(':first', $this->firstName);
	$statement -> bindParam(':last', $this->lastName);
	$statement -> bindParam(':email', $this->email);
	$statement -> bindParam(':password', $this->password);
	
	$statement -> execute();
	
	// Return the ID of the added question 
        return $db -> lastInsertId();
    }
    
    public function updateUser() {
        $db = self::getDb();
	
	$sql = "UPDATE Users SET FirstName = :first, LastName = :last, Email = :email, Password = :password
		WHERE UserID = :id";
        
	$statement = $db -> prepare($sql);
	$statement -> bindParam(':first', $this->firstName);
	$statement -> bindParam(':last', $this->lastName);
	$statement -> bindParam(':email', $this->email);
	$statement -> bindParam(':password', $this->password);
	$statement -> bindParam(':id', $this->id);
	
        $statement -> execute();
    }
    
    public function deleteUser() {
        $db = self::getDb();
	
	$sql = "DELETE FROM Users WHERE UserID = :id";
	$statement = $db -> prepare($sql);
	$statement -> bindParam(':id', $this->id);
	$statement -> execute();
    }
    
    private static function makeUserFromRow($row) {
        $user = new User($row['UserID'], $row['FirstName'], $row['LastName'], $row['Email'], $row['Password']);
        return $user;
    }
    
    private static function makeUsersFromRows($rows) {
        $result = array();
        foreach ($rows as $row) {
            $result[] = self::makeUserFromRow($row);
        }
        return $result;
    }
}