<?php include_once 'include/util.inc' ?>

<!DOCTYPE html>
<html>
	<head>
		<link rel="stylesheet" href="/Aptana/lab2/lab3/css/style.css" />
		
		<title><?php echo( $title ); ?></title>
	</head>
	<body>
		<div id="content-wrapper">


<?php include_once 'views/navigation.inc' ?>

<h1><?php echo (isLoggedIn()) ? 'LOGGED IN' : 'LOGGED OUT'; ?></h1>
<h2><?php echo ($id) ? "ID: $id" : '' ?></h2>

<h1> <?php echo( $title ); ?></h1>
<h3><?php echo( $subtitle ); ?></h3>

<!-- outer row loop -->
<?php foreach ($data as $row): ?>
	<div class="question">
		<a href="/Aptana/lab2/lab3/questions/view_question/<?php echo($row['QuestionID']); ?>"> <?php echo( $row['Title'] ); ?></a>
		<br />
		Posted: <?php echo( $row['Date'] ); ?>
		<br />
		<?php echo( ($row['Tags']) ? "Tags: " . $row['Tags'] : '' ); ?>
		<p class="question-content"> <?php echo( substr($row['Content'], 0, 240).".." ); ?></p>
	</div>
<?php endforeach ?>


<!-- <a href="/Aptana/lab2/lab3/questions/view_question/<?php echo($record['id']); ?>">[View]</a -->
<br />
<a href="/Aptana/lab2/lab3/questions/post_question/">[Post new question]</a>

	
	</div> <!-- End content wrapper -->
	<footer>
		&copy; Eric Davis
	</footer>
</body>
</html>