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
                //self::populateTables($db); COMMENTED OUT!!!!!!!
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

        // set up Users group for new registrants
        Logger::instance() -> info("Creating default Users group.");
        $g = new Group( array('name' => 'Users'));
        $g -> insert();
        foreach ($userperms as $name) {
            $g -> addPermission($permissions[$name]);
        }

        // set up the super-user
        Logger::instance() -> info("Creating default Administrators group.");
        $u = new User( array('firstName' => 'System', 'lastName' => 'Administrator', 'email' => 'admin@example.com', 'password' => 'asdF123$'));
        $u -> insert();
        $g = new Group( array('name' => 'Administrators'));
        $g -> insert();
        $g -> addUser($u);
        foreach ($adminperms as $name) {
            $g -> addPermission($permissions[$name]);
        }

    }
}