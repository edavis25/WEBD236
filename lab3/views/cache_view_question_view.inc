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
<hr />
<p>Posted on: <?php echo($question->getDate()); ?> by <a href="/Aptana/lab2/lab3/user/view_user/<?php echo( $question->getUserId() ); ?>"><?php echo( $question->getAuthorName() ); ?></a></p>
<p>Tags: <?php echo( ($question->getTags()) ? $question->getTags() : "<i>none</i>" ); ?></p>
<p class="question-content"><?php echo( nl2br($question->getContent()) ); ?></p>

<!-- Add edit/delete links if user is question author -->
<?php  if ($isAuthor) : ?>
<a href="/Aptana/lab2/lab3/questions/edit_question/<?php echo( $question->getId() ); ?>">[Edit]</a>
<a href="#" onclick="toggle('confirm-delete')">[Delete]</a>
<div id="confirm-delete" style="display: none;">Are you sure? <a href="/Aptana/lab2/lab3/questions/delete_question/<?php echo( $question->getId() ); ?>">yes</a> / <a href="#" onclick="toggle('confirm-delete')">no</a></div>
<?php  endif; ?>

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
