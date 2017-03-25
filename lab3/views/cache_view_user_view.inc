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
        <td><?php echo( $user->getFirstName() ); ?></td>
    </tr>
    <tr>
        <td>Last Name: </td>
        <td><?php echo( $user->getLastName() ); ?></td>
    </tr>
    <tr>
        <td>E-mail: </td>
        <td><?php echo( $user->getEmail() ); ?></td>
    </tr>
</table>

<br />

<?php  if ($ownsAccount) : ?>
<a href="/lab/lab3/user/edit_user/<?php echo( $user->getId() ); ?>">[ Edit ]</a>
<!-- a href="#" onclick="toggle('confirm-delete')">[Delete]</a>
<div id="confirm-delete" style="display: none;">Are you sure? <a href="/lab/lab3/user/delete_user/<?php echo( $user->getId() ); ?>">yes</a> / <a href="#" onclick="toggle('confirm-delete')">no</a></div -->
<div class="delete-wrapper">
    <a href="#" class="delete-button">[ Delete ]</a>&nbsp;
    <div class="confirm-delete" style="display: none;"> 
        <a href="/lab/lab3/user/delete_user/<?php echo( $user->getId() ); ?>"> yes</a> / <a href="#" class="delete-button">no</a>
    </div>
</div>
<?php  endif; ?>

<h2>Questions By <?php echo( $user->getFirstName() . " " . $user->getLastName() ); ?></h2>

<?php  foreach ($questions as $question): ?>
    <div class="question">
    <a href="/lab/lab3/questions/view_question/<?php echo($question->getId()); ?>"> <?php echo( $question->getTitle() ); ?></a>
    <br />
    Posted: <?php echo( $question->getDate() ); ?> by <a href="/lab/lab3/user/view_user/<?php echo( $question->getUserId() ); ?>"><?php echo( User::getFullName($question->getUserId()) ); ?></a>
    <br />
    <span>
<?php  
    $tags = explode(' ', $question->getTags());
    if ($tags[0]) {
        echo "Tags:";
    }
    foreach($tags as $tag) : 
?> 
    <a href="/lab/lab3/tag/view_questions/<?php echo( $tag ); ?>"><?php echo( $tag ); ?></a>
<?php   endforeach; ?>
</span>
    <p class="question-content"> <?php echo( substr($question->getContent(), 0, 240).".." ); ?></p>
</div>
<?php  endforeach ?>

	
</div> <!-- End content wrapper -->
<footer>
    &copy; Eric Davis
</footer>

<!-- Javascript to toggle yes/no confirmation of delete -->
<script src="/lab/lab3/js/jquery-3.2.0.min.js"></script>



<script type="text/javascript">
    /*
    function toggle(id) {
        //var elmt = document.getElementById(id);
        var elmts = document.getElementsByClassName(id);
        if (elmt) {
            // If hidden, show element
            var display = elmt.style.display;
            if (display == "none") {
                elmt.style.display = "inline-block";
            } else {
                // If already dispayed, hide element
                elmt.style.display = "none";
            }
        }
    }
    */
      function toggle(element) {
        if (element) {
           var display = element.style.display;
           if (display == "none") {
               element.style.display = "inline-block";
           }
           else {
               element.style.display = "none";
           }
       }
    }
   
     $('.delete-button').on('click', function() {
        var parent = $(this).closest('div[class^="delete-wrapper"]');
        
        var div = parent.children();
        toggle(div[1]);
    });
    
 
    
  

</script>
</body>
</html>


