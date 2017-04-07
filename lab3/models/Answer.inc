<?php
require_once 'models/Model.inc';

class Answer extends Model {
    private $userId;
    private $questionId;
    private $date;
    private $content;
    
    public function __construct($id, $userId, $questionId, $date, $content) {
        parent::__construct($id);
        $this->setUserId($userId);
        $this->setQuestionId($questionId);
        $this->setDate($date);
        $this->setContent($content);
    }
        
    public function getUserId() {
        return $this->userId;
    }
    public function setUserId($id) {
        $this->userId = $id;
    }
    
    public function getQuestionId() {
        return $this->questionId;
    }
    public function setQuestionId($id) {
        $this->questionId = $id;
    }
    
    public function getDate() {
        return $this->date;
    }
    public function setDate($date) {
        $this->date = $date;
    }
    
    public function getContent() {
        return $this->content;
    }
    public function setContent($content) {
        $this->content = $content;
    }
    
    public static function retrieveAnswerById($id) {
        //$db = self::getDb();
        $db = Db::getDb();
        
        $sql = "SELECT * FROM Answers WHERE AnswerID = :id";
        
        $statement = $db -> prepare($sql);
        $statement -> bindParam(':id', $id);
        $statement -> execute();
        
        $row = $statement -> fetch(PDO::FETCH_ASSOC);
        return self::makeAnswerFromRow($row);
    }
    
    public static function retrieveAnswersByQuestionId($id) {
        //$db = self::getDb();
        $db = Db::getDb();
        
        $sql = "SELECT * FROM Answers WHERE QuestionID = :id";
        
        $statement = $db -> prepare($sql);
        $statement -> bindParam(':id', $id);
        $statement -> execute();
        
        $rows = $statement -> fetchAll(PDO::FETCH_ASSOC);
        return self::makeAnswersFromRows($rows);
    }
    
    public static function deleteAnswersByQuestionId($id) {
        //$db = self::getDb();
        $db = Db::getDb();
        
        $sql = "DELETE FROM Answers WHERE QuestionID = :id";
        
        $statement = $db -> prepare($sql);
        $statement -> bindParam(':id', $id);
        $statement -> execute();
    }
    
    public static function deleteAnswersByUserId($id) {
        //$db = self::getDb();
        $db = Db::getDb();
        
        $sql = "DELETE FROM Answers WHERE UserID = :id";
        
        $statement = $db -> prepare($sql);
        $statement -> bindParam(':id', $id);
        $statement -> execute();
    }
    
    public function insertAnswer() {
	//$db = self::getDb();
        $db = Db::getDb();
	
	$sql = "INSERT INTO Answers (QuestionID, UserID, Date, Content)
			VALUES (:questionId, :userId, :date, :content)";
	
	$statement = $db -> prepare($sql);
        $statement -> bindParam(':questionId', $this->questionId);
        $statement -> bindParam(':userId', $this->userId);
        $statement -> bindParam(':date', $this->date);
        $statement -> bindParam(':content', $this->content);
		
	$statement -> execute();
	
	// Return the ID of the added question 
        return $db -> lastInsertId();
    }
    
    public function deleteAnswer() {
        //$db = self::getDb();
        $db = Db::getDb();

        $sql = "DELETE FROM Answers WHERE AnswerID = :id";
        
        $statement = $db -> prepare($sql);
        $statement -> bindParam(':id', $this->id);
        $statement -> execute();
    }
        
    private static function makeAnswerFromRow($row) {
        $answer = new Answer($row['AnswerID'], $row['UserID'], $row['QuestionID'], $row['Date'], $row['Content']);
        return $answer;
    }
    
    private static function makeAnswersFromRows($rows) {
        $result = array();
        foreach ($rows as $row) {
            $result[] = self::makeAnswerFromRow($row);
        }
        return $result;
    }
}
