<?php

// Connect to the database

global $db;
try {
    $db = new PDO('sqlite:lab2.db3');
} catch (PDOException $e) {
    die("Could not open database. " . $e->getMessage());
}


// simple function to handle any query with no parameters...
function adHocQuery($q) {
    global $db;
    $st = $db -> prepare($q);
    $st -> execute();
    return $st -> fetchAll(PDO::FETCH_ASSOC);
}
?>
