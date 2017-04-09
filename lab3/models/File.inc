<?php
include_once 'models/Model.inc';
include_once 'include/util.inc';
include_once 'models/Validator.inc';

class File extends Model {
    private $directory;
    private $origName;
    private $nameOnDisk;
    private $type;
    private $size;
    private $questionId;

    public function __construct($fields) {
        parent::__construct(safeParam($fields, 'FileID', null));
        $this -> setDirectory(safeParam($fields, 'Directory'));
        $this -> setOrigName(safeParam($fields, 'OrigName'));
        $this -> setNameOnDisk(safeParam($fields, 'DiskName'));
        $this -> setType(safeParam($fields, 'Type'));
        $this -> setSize(safeParam($fields, 'Size'));
        $this -> setQuestionId(safeParam($fields, 'QuestionID'));
    }

    public function fullPath() {
        return $this -> directory . DIRECTORY_SEPARATOR . $this -> nameOnDisk;
    }

    private function removeFromDisk() {
        $path = $this -> fullPath();
        if (is_file($path)) {
            unlink($path);
        }
    }

    private function moveOnDisk($to) {
        $old = $this -> fullPath();
        $new = $this -> directory . DIRECTORY_SEPARATOR . $to;
        if (is_file($old)) {
            rename($old, $new);
        }
        $this -> nameOnDisk = $to;
        return $this;
    }

    public function setDirectory($dir) {
        $this -> directory = $dir;
        return $this;
    }

    public function setOrigName($origName) {
        $this -> origName = $origName;
        return $this;
    }

    public function setNameOnDisk($nameOnDisk) {
        $this -> nameOnDisk = $nameOnDisk;
        return $this;
    }

    public function setType($type) {
        $this -> type = $type;
        return $this;
    }

    public function setSize($size) {
        $this -> size = $size;
        return $this;
    }

    public function setQuestionId($id) {
        $this -> questionId = $id;
        return $this;
    }

    public function getDirectory() {
        return $this -> directory;
    }

    public function getOrigName() {
        return $this -> origName;
    }

    public function getNameOnDisk() {
        return $this -> nameOnDisk;
    }

    public function getType() {
        return $this -> type;
    }

    public function getSize() {
        return $this -> size;
    }

    public function getQuestionId() {
        return $this -> questionId;
    }

    public function validate($throw = false) {
        $validator = new Validator();
        $validator -> required('dir', $this -> directory, "Directory is required");
        $validator -> required('origName', $this -> origName, "Original name is required");
        $validator -> required('nameOnDisk', $this -> nameOnDisk, "Name on disk is required");
        $validator -> required('type', $this -> type, "Type is required");
        $validator -> required('size', $this -> size, "Size is required");
        $validator -> required('questionId', $this -> questionId, "Question ID is required");
        if ($throw && $validator -> hasErrors()) {
            throw new IllegalStateException(implode(", ", $validator -> allErrors()));
        }
        return $validator;
    }

    private static function fromRows($rows) {
        $result = array();
        foreach ($rows as $row) {
            $result[] = new File($row);
        }
        return $result;
    }

    static function findById($id) {
        $db = Db::getDb();
        $st = $db -> prepare('SELECT * FROM Files WHERE FileID = :id');
        $st -> bindParam(':id', $id);
        $st -> execute();
        $row = $st -> fetch(PDO::FETCH_ASSOC);
        return new File($row);
    }

    static function findByQuestionID($id) {
        $db = Db::getDb();
        $st = $db -> prepare('SELECT * FROM Files WHERE QuestionID = :id');
        $st -> bindParam(':id', $id);
        $st -> execute();
        $rows = $st -> fetchAll(PDO::FETCH_ASSOC);
        return self::fromRows($rows);
    }
    
    static function findByDiskName($name) {
        $db = Db::getDb();
        $sql = "SELECT * FROM Files WHERE DiskName = :name";
        
        $statement = $db -> prepare($sql);
        $statement -> bindParam(':name', $name);
        $statement -> execute();
        
        $row = $statement -> fetch(PDO::FETCH_ASSOC);
        return new File($row);
    }

    function insert() {
        $this -> validate(true);
        $db = Db::getDb();
        
        $sql = "INSERT INTO Files (Directory, OrigName, DiskName, Type, Size, QuestionID) 
                VALUES (:dir, :origName, :nameOnDisk, :type, :size, :id)";
                
        $statement = $db -> prepare($sql);
        $statement -> bindParam(':dir', $this -> directory);
        $statement -> bindParam(':origName', $this -> origName);
        $statement -> bindParam(':nameOnDisk', $this -> nameOnDisk);
        $statement -> bindParam(':type', $this -> type);
        $statement -> bindParam(':size', $this -> size);
        $statement -> bindParam(':id', $this -> questionId);
        $statement -> execute();
        $this -> id = $db -> lastInsertId();
        return $this;
    }

    function update() {
        $this -> validate(true);
        $db = Db::getDb();
        
        $sql = "UPDATE Files SET
                    Directory = :dir, 
                    OrigName = :origName, 
                    Diskname = :nameOnDisk, 
                    Type = :type, 
                    Size = :size, 
                    QuestionID = :questionId 
                WHERE id = :id";
        
        $statement = $db -> prepare($sql);
        $statement -> bindParam(':dir', $this -> directory);
        $statement -> bindParam(':origName', $this -> origName);
        $statement -> bindParam(':nameOnDisk', $this -> nameOnDisk);
        $statement -> bindParam(':type', $this -> type);
        $statement -> bindParam(':size', $this -> size);
        $statement -> bindParam(':questionId', $this -> questionId);
        $statement -> bindParam(':id', $this -> id);
        $statement -> execute();
        return $this;
    }

    function delete() {
        $db = Db::getDb();
        $statement = $db -> prepare("DELETE FROM Files WHERE FileID = :id");
        $statement -> bindParam(':id', $this -> id);
        $statement -> execute();
        $this->removeFromDisk();
    }

}