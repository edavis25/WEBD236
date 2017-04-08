<?php
include_once 'models/Model.inc';
include_once 'models/User.inc';
include_once 'models/Permission.inc';
include_once 'models/Validator.inc';

class Group extends Model {

    protected $name;

    function __construct($id, $name) {
        parent::__construct($id);
        $this -> setName($name);
    }

    public function validate($throw = false) {
        $validator = new Validator();
        $validator -> required('name', $this -> name, "Group name is required");
        if ($throw && $validator -> hasErrors()) {
            throw new Exception(implode(", ", $validator -> allErrors()));
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

    private static function fromRows($rows) {
        $result = array();
        foreach ($rows as $row) {
            $result[] = new Group($row['GroupID'], $row['Name']);
        }
        return $result;
    }

    public static function findAll() {
        $db = Db::getDb();
        $st = $db -> prepare("SELECT * FROM Groups ORDER BY Name");
        $st -> execute();
        return self::fromRows($st -> fetchAll(PDO::FETCH_ASSOC));
    }

    public static function findById($id) {
        $db = Db::getDb();
        $st = $db -> prepare("SELECT * FROM Groups WHERE GroupID = :id");
        $st -> bindParam(':id', $id);
        $st -> execute();
        
        $row = $st -> fetch(PDO::FETCH_ASSOC);
        return new Group($row['GroupID'], $row['Name']);
    }

    public static function findByName($name) {
        $db = Db::getDb();
        $st = $db -> prepare("SELECT * FROM Groups WHERE Name = :name");
        $st -> bindParam(':name', $name);
        $st -> execute();
        
        $row = $st -> fetch(PDO::FETCH_ASSOC);
        return new Group($row['GroupID'], $row['Name']);
    }

    public function insert() {
        $db = Db::getDb();
        $this -> validate(true);
        $this -> clean();
        $statement = $db -> prepare("INSERT INTO Groups (Name) VALUES (:name)");
        $statement -> bindParam(':name', $this -> name);
        $statement -> execute();
        $this -> setId($db -> lastInsertId());
        return $this;
    }

    public function update() {
        $db = Db::getDb();
        $this -> validate(true);
        $this -> clean();
        $statement = $db -> prepare("UPDATE Groups SET Name = :name WHERE GroupID = :id");
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
        $statement = $db -> prepare("DELETE FROM Groups WHERE GroupID = :id");
        $statement -> bindParam(':id', $id);
        $statement -> execute();
    }

    public static function findByUserId($userId) {
        $db = Db::getDb();
        $statement = $db -> prepare("SELECT * FROM Groups WHERE Groups.GroupID IN (SELECT Groups.GroupID from Groups, UserGroups WHERE Groups.GroupID = UserGroups.GroupID AND UserGroups.UserID = :userId) ORDER BY Name");
        $statement -> bindParam(':userId', $userId);
        $statement -> execute();
        return self::fromRows($statement->fetchAll(PDO::FETCH_ASSOC));
    }

    public static function findByNotUserId($userId) {
        $db = Db::getDb();
        $statement = $db -> prepare("SELECT * FROM Groups WHERE Groups.GroupID NOT IN (SELECT Groups.GroupID from Groups, UserGroups WHERE Groups.GroupID = UserGroups.GroupID AND UserGroups.UserID = :userId) ORDER BY Name");
        $statement -> bindParam(':userId', $userId);
        $statement -> execute();
        return self::fromRows($statement->fetchAll(PDO::FETCH_ASSOC));
    }

    public function addUser($user) {
        $db = Db::getDb();
        $statement = $db -> prepare("INSERT INTO UserGroups (GroupID, UserID) VALUES (:groupId, :userId)");
        $statement -> bindValue(':groupId', $this -> getId());
        $statement -> bindValue(':userId', $user -> getId());
        $statement -> execute();
    }

    public function removeUser($user) {
        $db = Db::getDb();
        $statement = $db -> prepare("DELETE FROM UserGroups WHERE GroupID = :groupId AND UserID = :userId");
        $statement -> bindValue(':groupId', $this -> getId());
        $statement -> bindValue(':userId', $user -> getId());
        $statement -> execute();
    }

    public function addPermission($permission) {
        $db = Db::getDb();

        $statement = $db -> prepare("INSERT INTO GroupPermissions (GroupID, PermissionID) VALUES (:groupId, :permissionId)");
        $statement -> bindValue(':groupId', $this -> getId());
        $statement -> bindValue(':permissionId', $permission -> getId());
        $statement -> execute();
    }

    public function removePermission($permission) {
        $db = Db::getDb();
        $statement = $db -> prepare("DELETE FROM GroupPermissions WHERE PermissionID = :permissionId AND GroupID = :groupId");
        $statement -> bindValue(':groupId', $this -> getId());
        $statement -> bindValue(':permissionId', $permission -> getId());
        $statement -> execute();
    }

    public function getMembers() {
        $db = Db::getDb();
        $sql = "SELECT Users.UserID AS UserID,
                    Users.FirstName AS FirstName, 
                    Users.LastName AS LastName, 
                    Users.Email AS Email,
                    Users.Password AS Password
                FROM Users, UserGroups 
                WHERE Users.UserID = UserGroups.UserID and UserGroups.GroupID = :id 
                ORDER BY LastName, FirstName";
        
        $statement = $db -> prepare($sql);
        $statement -> bindParam(':id', $this -> id);
        $statement -> execute();
        $rows = $statement -> fetchAll(PDO::FETCH_ASSOC);
        return User::makeUsersFromRows($rows);
    }

    public function getNonMembers() {
        $db = Db::getDb();
        $statement = $db -> prepare("SELECT * FROM Users WHERE Users.UserID NOT IN (SELECT Users.UserID FROM Users, UserGroups WHERE Users.UserID = UserGroups.UserID and UserGroups.GroupID = :id) ORDER BY LastName, FirstName;");
        $statement -> bindParam(':id', $this -> id);
        $statement -> execute();
        $rows = $statement -> fetchAll(PDO::FETCH_ASSOC);
        return User::makeUsersFromRows($rows);
    }

    public function getPermissions() {
        $db = Db::getDb();
        $statement = $db -> prepare("SELECT Permissions.PermissionID AS id, Permissions.Name as name FROM Permissions, GroupPermissions WHERE Permissions.PermissionID = GroupPermissions.PermissionID AND GroupPermissions.GroupID = :id ORDER BY name");
        $statement -> bindParam(':id', $this -> id);
        $statement -> execute();
        $rows = $statement -> fetchAll(PDO::FETCH_ASSOC);
        return Permission::fromRows($rows);
    }

    public function getNonPermissions() {
        $db = Db::getDb();
        $statement = $db -> prepare("SELECT Permissions.PermissionID AS id, Permissions.Name as name FROM Permissions WHERE Permissions.PermissionID NOT IN (SELECT Permissions.PermissionID FROM Permissions, GroupPermissions WHERE Permissions.PermissionID = GroupPermissions.PermissionID and GroupPermissions.GroupID = :id) ORDER BY Name;");
        $statement -> bindParam(':id', $this -> id);
        $statement -> execute();
        $rows = $statement -> fetchAll(PDO::FETCH_ASSOC);
        return Permission::fromRows($rows);
    }

}