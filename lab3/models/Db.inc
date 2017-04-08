<?php

include_once ('models/Permission.inc');
include_once ('models/User.inc');
include_once ('models/Group.inc');
include_once ('include/Logger.inc');

class Db {
    public static function getDb() {
        try {
            $fileName = "lab2.db3";

            // see if we need to create tables
            $makeDb = !file_exists($fileName);
            $db = new PDO("sqlite:${fileName}");

            // force exceptions for better debugging.
            $db -> setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

            // force cascading deletes on foreign key constraints
            $st = $db -> prepare("PRAGMA foreign_keys = ON");
            $st -> execute();

            if ($makeDb) {
                self::makeTables($db);
                self::populateTables($db);
            }

        } catch (PDOException $e) {
            die("Could not open database. " . $e -> getMessage());
        }
        return $db;
    }

    private static function makeTables(&$db) {
        
        Logger::instance() -> info("Creating tables");
        // @formatter:off
        $statements = array( 
            "CREATE TABLE Users (
                UserID    INTEGER PRIMARY KEY AUTOINCREMENT
                          NOT NULL
                          UNIQUE,
                FirstName TEXT    NOT NULL,
                LastName  TEXT    NOT NULL,
                Email     TEXT    NOT NULL,
                Password  TEXT    NOT NULL
            )",
            "CREATE TABLE Groups (
                GroupID INTEGER PRIMARY KEY AUTOINCREMENT
                        NOT NULL,
                Name    TEXT    NOT NULL
            )",
            "CREATE TABLE Permissions (
                PermissionID INTEGER PRIMARY KEY AUTOINCREMENT
                             NOT NULL,
                Name         TEXT    NOT NULL
            )",
            "CREATE TABLE UserGroups (
                UserID  INTEGER REFERENCES Users (UserID) ON DELETE CASCADE
                                                          ON UPDATE CASCADE
                                                          NOT NULL,
                GroupID INTEGER REFERENCES Groups (GroupID) ON DELETE CASCADE
                                                            ON UPDATE CASCADE
                                                            NOT NULL
            )",
            "CREATE TABLE GroupPermissions (
                GroupID      INTEGER NOT NULL
                             REFERENCES Groups (GroupID) ON DELETE CASCADE
                                                         ON UPDATE CASCADE,
                PermissionID INTEGER 
                             REFERENCES Permissions (PermissionID) ON DELETE CASCADE
                                                                   ON UPDATE CASCADE
                                                                   NOT NULL
            )",
            "CREATE TABLE Answers (
                AnswerID   INTEGER PRIMARY KEY AUTOINCREMENT
                           NOT NULL
                           UNIQUE,
                QuestionID INTEGER REFERENCES Questions (QuestionID) ON DELETE CASCADE
                                                                     ON UPDATE CASCADE
                           NOT NULL,
                UserID     INTEGER REFERENCES Users (UserID) ON DELETE CASCADE
                                                             ON UPDATE CASCADE
                           NOT NULL,
                Date       DATE    NOT NULL,
                Content    TEXT    NOT NULL
            )",
            "CREATE TABLE Questions (
                QuestionID INTEGER PRIMARY KEY AUTOINCREMENT
                           NOT NULL,
                Date       DATE    NOT NULL,
                Title      TEXT    NOT NULL,
                Content    TEXT    NOT NULL,
                Tags       TEXT,
                UserID     INTEGER REFERENCES Users (UserID) 
                           NOT NULL
            )"
         );
        // @formatter:on

        $db -> beginTransaction();
        foreach ($statements as $statement) {
            $st = $db -> prepare($statement);
            $st -> execute();
        }
        $db -> commit();
    }

    private static function populateTables(&$db) {
        // create the permissions
        $userperms = array('answer_create');
        $editperms = array('answer_delete', 'question_create', 'question_delete', 'question_edit');
        $adminperms = array('admin_page', 'user_delete', 'user_edit');
        $permissions = array();
        $allperms = array($adminperms, $userperms, $editperms);
        foreach ($allperms as $perms) {
            foreach ($perms as $name) {
                $p = new Permission( array('name' => $name));
                $p -> insert();
                $permissions[$name] = $p;
            }
        }
     
        // Setup "Users" group permissions
        Logger::instance() -> info("Creating default Users group permissions.");
        //$g = new Group( array('name' => 'Users'));
        $g = new Group(null, 'Users');
        $g -> insert();
        foreach ($userperms as $name) {
            $g -> addPermission($permissions[$name]);
        }
        
        // Setup "Editors" group permissions
        Logger::instance() -> info("Creating default Editors group permissions.");
        $g = new Group(null, 'Editors');
        $g -> insert();
        foreach ($editperms as $name) {
            $g -> addPermission($permissions[$name]);
        }
        
        // Setup "Admin" group permissions
        Logger::instance() -> info("Creating default Admin group permissions.");
        $g = new Group(null, 'Administrators');
        $g -> insert();
        foreach ($adminperms as $name) {
            $g -> addPermission($permissions[$name]);
        }
        
        // Set up the super-user
        Logger::instance() -> info("Creating default super user.");
        $user = new User(null, 'System', 'Administrator', 'admin', 'admin');
        $id = $user -> insertUser();
        // Get user from DB to include autoincremented ID
        $user = User::retrieveUserById($id);
        
        $groups = Group::findAll();
        foreach ($groups as $group) {
            $group -> addUser($user);
        }
    }
    
    protected static function adHocQuery($q) {
        $db = self::getDb();
        $st = $db -> prepare($q);
        $st -> execute();
        return $st -> fetchAll(PDO::FETCH_ASSOC);
    }
}
