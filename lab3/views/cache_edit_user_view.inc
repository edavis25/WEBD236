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
<form action="/Aptana/lab2/lab3/<?php echo( $form_action ); ?>" method="post">
	<label for="first-name">First Name:</label><br />
	<input type="text" id="first-name" name="first-name" class="full-width" value="<?php echo( isset($inputs['first_name']) ? $inputs['first_name'] : '' ); ?>" />
	<br /><br />
	<label for="last-name">Last Name:</label><br />
	<input type="text" id="last-name" name="last-name" class="full-width" value="<?php echo( isset($inputs['last_name']) ? $inputs['last_name'] : '' ); ?>" />
	<br /><br />
	<label for="username">Email Address:</label><br />
	<input type="text" id="username" name="username" class="full-width" value="<?php echo( isset($inputs['username']) ? $inputs['username'] : '' ); ?>" />
	<br /><br />
	<label for="password">Password:</label><br />
	<input type="text" id="password" name="password" class="full-width" value="<?php echo( isset($inputs['password']) ? $inputs['password'] : '' ); ?>" />
	<br /><br />
	<input type="submit" id="login-submit" name="login-submit" value="<?php echo( $button_text ); ?>" />
</form>

	
	</div> <!-- End content wrapper -->
	<footer>
		&copy; Eric Davis
	</footer>
</body>
</html>
