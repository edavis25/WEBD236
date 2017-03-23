<?php
class Model {
    protected $id;

    public function __construct($id = null) {
        if ($id) {
            $this -> setId($id);
        }
    }

    public function getId() {
        return $this -> id;
    }

    public function setId($id) {
        $this -> id = $id;
        return $this;
    }

    protected static function getDb() {
        try {
            $db = new PDO('sqlite:lab2.db3');
        } catch (PDOException $e) {
            die("Could not open database. " . $e -> getMessage());
        }
        return $db;
    }

    protected static function adHocQuery($q) {
        $db = self::getDb();
        $st = $db -> prepare($q);
        $st -> execute();
        return $st -> fetchAll(PDO::FETCH_ASSOC);
    }

}
?>
