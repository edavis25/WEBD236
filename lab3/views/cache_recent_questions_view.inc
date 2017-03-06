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


<h1><?php echo (isLoggedIn()) ? 'LOGGED IN' : 'LOGGED OUT'; ?></h1>
<h2><?php echo( isset($_SESSION['UserID']) ? $_SESSION['UserID'] : ''); ?></h2>

<h1> <?php echo( $title ); ?></h1>
<h3><?php echo( $subtitle ); ?></h3>

<!-- outer row loop -->
<?php foreach ($data as $row): ?>
	<div class="question">
		<a href="/Aptana/lab2/lab3/questions/view_question/<?php echo($row['QuestionID']); ?>"> <?php echo( $row['Title'] ); ?></a>
		<br />
		Posted: <?php echo( $row['Date'] ); ?> by <a href="/Aptana/lab2/lab3/user/view_user/<?php echo( $row['UserID'] ); ?>"><?php echo( $row['Author'] ); ?></a>
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