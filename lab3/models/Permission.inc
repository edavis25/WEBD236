<?php
include_once 'models/Model.inc';

class Permission extends Model {

    protected $name;
    
    function __construct($fields = array()) {
        parent::__construct(safeParam($fields, 'id', null));
        $this -> setName(safeParam($fields, 'name', null));
    }
    

    public function validate($throw = false) {
        $validator = new Validator();
        $validator -> required('name', $this -> name, "Permission name is required");
        if ($throw && $validator -> hasErrors()) {
            throw new IllegalStateException(implode(", ", $validator -> allErrors()));
        }
        return $validator;
    }

    private function clean() {
        $this -> name = htmlentities($this -> name, ENT_QUOTES);
    }

    public function setName($name) {
        $this -> name = trim($name);
        return $this;
    }

    public function getName() {
        return $this -> name;
    }

    public static function fromRows($rows) {
        $result = array();
        foreach ($rows as $row) {
            $result[] = new Permission($row);
        }
        return $result;
    }

    public static function findAll() {
        $db = Db::getDb();
        $st = $db -> prepare("SELECT * FROM Permissions ORDER BY Name");
        $st -> execute();
        return self::fromRows($st -> fetchAll(PDO::FETCH_ASSOC));
    }
    
    public static function findById($id) {
        $db = Db::getDb();
        $st = $db -> prepare("SELECT PermissionID as id, Name as name FROM Permissions WHERE PermissionID = :id");
        $st -> bindParam(':id', $id);
        $st -> execute();
        
        return new Permission($st -> fetch(PDO::FETCH_ASSOC));
    }

    public static function findByName($name) {
        $db = Db::getDb();
        $st = $db -> prepare("SELECT * FROM Permissions WHERE Name = :name");
        $st -> bindParam(':name', $name);
        $st -> execute();
        return new Permission($st -> fetch(PDO::FETCH_ASSOC));
    }

    public function insert() {
        $db = Db::getDb();
        $this -> validate(true);
        $this -> clean();
        $statement = $db -> prepare("INSERT INTO Permissions (Name) VALUES (:name)");
        $statement -> bindParam(':name', $this -> name);
        $statement -> execute();
        $this -> setId($db -> lastInsertId());
        return $this;
    }

    public function update() {
        $db = Db::getDb();
        $this -> validate(true);
        $this -> clean();
        $statement = $db -> prepare("UPDATE Permissions SET Name = :name WHERE PermissionID = :id");
        $statement -> bindParam(':name', $this -> name);
        $statement -> bindParam(':id', $this -> id);
        $statement -> execute();
        return $this;
    }

    public function delete() {
        self::deleteById($this -> getId());
    }

    private static function deleteById($id) {
        $db = Db::getDb();
        $statement = $db -> prepare("DELETE FROM Permissions WHERE PermissionID = :id");
        $statement -> bindParam(':id', $id);
        $statement -> execute();
    }

}