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

<form action="/Aptana/lab2/lab3/questions/edit_question" method="post">
	<label for="title">Title</label>
	<br />
        <input type="text" id="title" name="title" class="full-width" value= "<?php echo( $question->getTitle() ); ?>" />
	<br />
	<label for="content-textarea">Content</label>
	<br />
        <textarea name="content" id="content-textarea" rows="15" class="full-width"><?php echo( $question->getContent() ); ?></textarea>
	<br />
	<label for="tags">Tags</label>
        <input type="text" id="tags" name="tags" class="full-width" value="<?php echo( $question->getTags() ); ?>" />
	<br /><br />
        <input type="hidden" name="id" value="<?php echo( $question->getId() ); ?>" />
	<input type="submit" value="Save Changes" id="submit-question" />
</form>
<br /><br />
<a href="/Aptana/lab2/lab3/index">&lt;&lt; Back</a>

	
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