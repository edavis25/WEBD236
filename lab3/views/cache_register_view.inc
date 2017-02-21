<!DOCTYPE html>
<html>
	<head>
		<link rel="stylesheet" href="/Aptana/lab2/lab3/css/style.css" />
		
		<title><?php echo( $title ); ?></title>
	</head>
	<body>
		<div id="content-wrapper">


<?php include_once 'views/navigation.inc' ?>

<h1><?php echo( $title ); ?></h1>

<div id="errors">
	<?php echo( isset($errors) ? $errors."<br />" : '' ); ?>
</div>
<br />
<form action="/Aptana/lab2/lab3/login" method="post">
	<label for="username">Username:</label><br />
	<input type="text" id="username" name="username" class="full-width" />
	<br /><br />
	<label for="password">Password:</label><br />
	<input type="text" id="password" name="password" class="full-width" />
	<br /><br />
	<input type="submit" id="login-submit" name="login-submit" />
</form>

	
	</div> <!-- End content wrapper -->
	<footer>
		&copy; Eric Davis
	</footer>
</body>
</html>
