<?php
require_once 'models/Model.inc';

class Question extends Model {
    private $date;
    private $title;
    private $content;
    private $tags;
    private $userId;
    
    public function __construct($id, $date, $title, $content, $tags, $userId) {
        parent::__construct($id);
        $this->setDate($date);
        $this->setTitle($title);
        $this->setContent($content);
        $this->setTags($tags);
        $this->setUserId($userId);
    }
    
    public function getDate() {
        return $this->date;
    }
    public function setDate($date) {
        $this->date = $date;
    }
    
    public function getTitle() {
        return $this->title;
    }
    public function setTitle($title) {
        $this->title = $title;
    }
    
    public function getContent() {
        return $this->content;
    }
    public function setContent($content) {
        $this->content = $content;
    }
    
    public function getTags() {
        return $this->tags;
    }
    public function setTags($tags) {
        $this->tags = $tags;
    }
    
    public function getUserId() {
        return $this->userId;
    }
    public function setUserId($id) {
        $this->userId = $id;
    }
    
    public static function retrieveRecentQuestions($limit = 5) {
        $db = Db::getDb();
        
        $st = $db -> prepare('SELECT * FROM Questions ORDER BY Date DESC LIMIT :limit');
        $st->bindParam(':limit', $limit);
        $st -> execute();
        
        $rows = $st -> fetchAll(PDO::FETCH_ASSOC);
        return self::makeQuestionsFromRows($rows);
    }
    
    public static function retrieveQuestionById($id) {
        $db = Db::getDb();
        
        $st = $db -> prepare('SELECT * FROM Questions WHERE QuestionID = :id');
        $st -> bindParam(':id', $id);
        $st -> execute();
        
        $row = $st -> fetch(PDO::FETCH_ASSOC);
        return self::makeQuestionFromRow($row);
    }
    
    public static function retrieveQuestionsByUserId($id) {
        $db = Db::getDb();
        
        $sql = "SELECT * FROM Questions WHERE UserID = :id ORDER BY Date DESC";
	
	$statement = $db -> prepare($sql);
	$statement -> bindParam(':id', $id);
	$statement -> execute();
	
        $rows = $statement -> fetchAll(PDO::FETCH_ASSOC);
	return self::makeQuestionsFromRows($rows);
    }
    
    public static function retrieveQuestionsByTagName($tag) {
        $db = Db::getDb();
        
        // Because I couldn't figure out how to use REGEXPs with the PDO...
        $sql = "SELECT * FROM Questions WHERE ' ' || Tags || ' ' LIKE :tag";
        $tag = '% '.$tag.' %';
        
        $statement = $db -> prepare($sql);
        $statement -> bindParam(':tag', $tag);
        $statement -> execute();
       
        $rows = $statement -> fetchAll(PDO::FETCH_ASSOC);
        
        return self::makeQuestionsFromRows($rows);
    }
    
    public function insertQuestion() {
        $db = Db::getDb();
	
	$sql = "INSERT INTO Questions (Date, Title, Content, Tags, UserID) 
			VALUES (:date, :title, :content, :tags, :userid)";
	
	$statement = $db -> prepare($sql);
        $statement -> bindParam(':date', $this->date);
	$statement -> bindParam(':title', $this->title);
	$statement -> bindParam(':content', $this->content);
	$statement -> bindParam(':tags', $this->tags);
	$statement -> bindParam(':userid', $this->userId);
	
	$statement -> execute();
	
	// Return the ID of the added question 
        return $db -> lastInsertId();
    }
    
    public function deleteQuestion() {
        $db = Db::getDb();

        $sql = "DELETE FROM Questions WHERE QuestionID = :id";
        $statement = $db -> prepare($sql);
        
        $statement -> bindParam(':id', $this->id);
        $statement -> execute();
    }
    
    public static function deleteQuestionsByUserId($id) {
        $db = Db::getDb();
	
	$sql = "DELETE FROM Questions WHERE UserID = :id";
	
        $statement = $db -> prepare($sql);
	$statement -> bindParam(':id', $id);
	$statement -> execute();
    }
    
    public function updateQuestion() {
        $db = Db::getDb();
		
	$sql = "UPDATE Questions SET Title = :title, Content = :content, Tags = :tags WHERE QuestionID = :id";
        
	$statement = $db -> prepare($sql);
	$statement -> bindParam(':title', $this->title);
	$statement -> bindParam(':content', $this->content);
	$statement -> bindParam(':tags', $this->tags);
        $statement -> bindParam(':id', $this->id);
        
        $statement -> execute();
}

    private static function makeQuestionFromRow($row) {
        $question = new Question($row['QuestionID'], $row['Date'], $row['Title'], $row['Content'], $row['Tags'], $row['UserID']);
        return $question;
    }
    
    private static function makeQuestionsFromRows($rows) {
        $result = array();
        foreach ($rows as $row) {
            $result[] = self::makeQuestionFromRow($row);
        }
        return $result;
    }
}