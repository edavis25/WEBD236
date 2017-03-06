<?php include_once 'include/util.inc' ?>

<!DOCTYPE html>
<html>
	<head>
		<link rel="stylesheet" href="/lab/lab3/css/style.css" />
		
		<title><?php echo( $title ); ?></title>
	</head>
	<body>
		<!-- Page wrapper -->
		<div id="content-wrapper">
			
			<!-- Navigation bar -->
			<div id="nav">
				<ul>
					
					<?php if (isLoggedIn()) : ?>
						<li><a href="/lab/lab3/logout">Logout</a></li>
						<li><a href="/lab/lab3/user/view_user/<?php echo(safeParam($_SESSION, 'UserID', false)); ?>">My Profile</a></li>
					<?php  else : ?>
						<li><a href="/lab/lab3/login">Login</a></li>
						<li><a href="/lab/lab3/user/register">Register</a></li>	
					<?php  endif; ?>
					
					<!-- Home link always present -->
					<li><a href="/lab/lab3/index">Home</a></li>
				</ul>
			</div>
			
			<!-- User greeting -->
			<div id="greeting">
				<?php  if (isLoggedIn()) : ?>
					<?php echo( "Welcome, " . safeParam($_SESSION, 'FirstName', false) ." ". safeParam($_SESSION, 'LastName', false) ."!" ); ?>
				<?php  endif; ?>
			</div>


<h1><?php echo( $title ); ?></h1>

<table>
	<tr>
		<td>First Name: </td>
		<td><?php echo( $data['FirstName'] ); ?></td>
	</tr>
	<tr>
		<td>Last Name: </td>
		<td><?php echo( $data['LastName'] ); ?></td>
	</tr>
	<tr>
		<td>E-mail: </td>
		<td><?php echo( $data['Email'] ); ?></td>
	</tr>
</table>

<br />

<?php  if ($ownsAccount) : ?>
<a href="/lab/lab3/user/edit_user">[Edit]</a>
<a href="#" onclick="toggle('confirm-delete')">[Delete]</a>
<div id="confirm-delete" style="display: none;">Are you sure? <a href="/lab/lab3/user/delete_user">yes</a> / <a href="#" onclick="toggle('confirm-delete')">no</a></div>
<?php  endif; ?>

<h2>Questions By <?php echo($data['FirstName'] ." ". $data['LastName']); ?></h2>

<?php  foreach ($questions as $row): ?>
	<div class="question">
		<a href="/lab/lab3/questions/view_question/<?php echo($row['QuestionID']); ?>"> <?php echo( $row['Title'] ); ?></a>
		<br />
		Posted: <?php echo( $row['Date'] ); ?> by <a href="/lab/lab3/user/view_user/<?php echo( $row['UserID'] ); ?>"><?php echo( $data['FirstName'] ." ". $data['LastName'] ); ?></a>
		<br />
		<?php echo( ($row['Tags']) ? "Tags: " . $row['Tags'] : '' ); ?>
		<p class="question-content"> <?php echo( substr($row['Content'], 0, 240).".." ); ?></p>
	</div>
<?php  endforeach ?>

	
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