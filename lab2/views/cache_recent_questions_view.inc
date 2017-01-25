<!DOCTYPE html>
<html>
	<head>
		<link rel="stylesheet" href="/Aptana/lab2/lab2/css/style.css" />
		<title><?php echo( $title ); ?></title>
	</head>
	<body>
		
		<div id="content-wrapper">


<?php	
/*
echo "RECENT QUESTIONS VIEW!!! <br />";
 
foreach ($data as $row)
{
	foreach ($row as $col)
	{
		echo "$col <br />";
	}
}

//echo "TEST DATE: ".$data[0]['Date'];

 */
?>

<h1> <?php echo( $title ); ?></h1>
<h3><?php echo( $subtitle ); ?></h3>


<!-- outer row loop -->
<?php foreach ($data as $row): ?>
	<div class="question">
		<a href="/Aptana/lab2/lab2/questions/view_question/<?php echo($row['QuestionID']); ?>"> <?php echo( $row['Title'] ); ?></a>
		<br />
		Posted: <?php echo( $row['Date'] ); ?>
		<br />
		Tags: <?php echo( $row['Tags'] ); ?>
		<p class="question-content"> <?php echo( substr($row['Content'], 0, 240).".." ); ?></p>
	</div>
<?php endforeach ?>


<!-- <a href="/Aptana/lab2/lab2/questions/view_question/<?php echo($record['id']); ?>">[View]</a -->
<br />
<a href="/Aptana/lab2/lab2/questions/post_question/">[Post new question]</a>