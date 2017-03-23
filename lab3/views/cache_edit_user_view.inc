<?php include_once 'include/util.inc' ?>

<!DOCTYPE html>
<html>
	<head>
		<link rel="stylesheet" href="/Aptana/lab2/lab3/css/style.css" />
		
		<title><?php echo( $title ); ?></title>
	</head>
	<body>
		<!-- Page wrapper -->
		<div id="content-wrapper">
			
			<!-- Navigation bar -->
			<div id="nav">
				<ul>
					
					<?php if (isLoggedIn()) : ?>
						<li><a href="/Aptana/lab2/lab3/logout">Logout</a></li>
						<li><a href="/Aptana/lab2/lab3/user/view_user/<?php echo(safeParam($_SESSION, 'UserID', false)); ?>">My Profile</a></li>
					<?php  else : ?>
						<li><a href="/Aptana/lab2/lab3/login">Login</a></li>
						<li><a href="/Aptana/lab2/lab3/user/register">Register</a></li>	
					<?php  endif; ?>
					
					<!-- Home link always present -->
					<li><a href="/Aptana/lab2/lab3/index">Home</a></li>
				</ul>
			</div>
			
			<!-- User greeting -->
			<div id="greeting">
				<?php  if (isLoggedIn()) : ?>
					<?php echo( "Welcome, " . safeParam($_SESSION, 'FirstName', false) ." ". safeParam($_SESSION, 'LastName', false) ."!" ); ?>
				<?php  endif; ?>
			</div>


<h1><?php echo( $title ); ?></h1>

<div id="errors">
    <?php echo( isset($errors) ? $errors."<br />" : '' ); ?>
</div>

<br />

<form action="/Aptana/lab2/lab3/<?php echo( $form_action ); ?>" method="post">
    <label for="first-name">First Name:</label><br />
    <input type="text" id="first-name" name="first-name" class="full-width" value="<?php echo( $user->getFirstName() ); ?>" />

    <label for="last-name">Last Name:</label><br />
    <input type="text" id="last-name" name="last-name" class="full-width" value="<?php echo( $user->getLastName() ); ?>" />

    <label for="username">Email Address:</label><br />
    <input type="text" id="username" name="username" class="full-width" value="<?php echo( $user->getEmail() ); ?>" />

    <label for="password">Password:</label><br />
    <input type="text" id="password" name="password" class="full-width" value="<?php echo( $user->getPassword() ); ?>" />

    <input type="hidden" id="user-id" name="user-id" value="<?php echo( $user->getId() ); ?>" />
    
    <input type="submit" id="login-submit" name="login-submit" value="<?php echo( $button_text ); ?>" />
</form>

	
	</div> <!-- End content wrapper -->
	<footer>
		&copy; Eric Davis
	</footer>
	
	<!-- Javascript to toggle yes/no confirmation of delete -->
	<script type="text/javascript">
		function toggle(id) {
	    	var elmt = document.getElementById(id);
    
	    	if (elmt) {
    			// If hidden, show element
        		var display = elmt.style.display;
				if (display == "none") {
        	    	elmt.style.display = "inline-block";
    	    	}
	         else {
         		// If already dispayed, hide element
        	    elmt.style.display = "none";
    	    	}
	    	}
		}
	</script>
</body>
</html>
