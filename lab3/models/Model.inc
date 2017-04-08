<?php
include_once 'models/Db.inc';
include_once 'include/util.inc';
include_once 'include/Logger.inc';

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
}
