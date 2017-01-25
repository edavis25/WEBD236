<?php
/*
echo "VIEW QUESTION! <br />";

foreach ($question as $row)
{
	echo "$row <br />";
}

echo $question['Date'];
*/
?>


<!DOCTYPE html>
<html>
	<head>
		<link rel="stylesheet" href="/Aptana/lab2/lab2/css/style.css" />
		<title><?php echo( $title ); ?></title>
	</head>
	<body>
		
		<div id="content-wrapper">


<h1><?php echo($question['Title']); ?></h1>
<p>Posted on: <?php echo($question['Date']); ?></p>
<p>Tags: <?php echo($question['Tags']); ?></p>
<p><?php echo($question['Content']); ?></p>

<a href="">[Edit]</a>
<a href="">[Delete]</a>
<br /><br />
<a href="/Aptana/lab2/lab2/index">&lt;&lt; Back</a>
