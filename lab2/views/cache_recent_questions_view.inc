<!DOCTYPE html>
<html>
	<head>
		<link rel="stylesheet" href="/lab/lab2/css/style.css" />
		
		<title><?php echo( $title ); ?></title>
	</head>
	<body>
		<div id="content-wrapper">


<h1> <?php echo( $title ); ?></h1>
<h3><?php echo( $subtitle ); ?></h3>


<!-- outer row loop -->
<?php foreach ($data as $row): ?>
	<div class="question">
		<a href="/lab/lab2/questions/view_question/<?php echo($row['QuestionID']); ?>"> <?php echo( $row['Title'] ); ?></a>
		<br />
		Posted: <?php echo( $row['Date'] ); ?>
		<br />
		<?php echo( ($row['Tags']) ? "Tags: " . $row['Tags'] : '' ); ?>
		<p class="question-content"> <?php echo( substr($row['Content'], 0, 240).".." ); ?></p>
	</div>
<?php endforeach ?>


<!-- <a href="/lab/lab2/questions/view_question/<?php echo($record['id']); ?>">[View]</a -->
<br />
<a href="/lab/lab2/questions/post_question/">[Post new question]</a>

	
	</div> <!-- End content wrapper -->
	<footer>
		&copy; Eric Davis
	</footer>
</body>
</html>