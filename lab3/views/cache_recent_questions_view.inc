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


<h1> <?php echo( isset($title) ? $title : '' ); ?></h1>
<h3><?php echo( isset($subtitle) ? $subtitle : '' ); ?></h3>

<!-- outer row loop -->
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
<?php  endforeach; ?>

<br />

<?php  if (isLoggedIn()) : ?>
    <a href="/lab/lab3/questions/post_question/<?php echo( isset($prefillTag) ? $prefillTag : '' ); ?>"><?php echo( $newQuestionButtonText ); ?></a>
<?php  endif; ?>

	
</div> <!-- End content wrapper -->
<footer>
    &copy; Eric Davis
</footer>

<!-- Javascript to toggle yes/no confirmation of delete -->
<script src="/lab/lab3/js/jquery-3.2.0.min.js"></script>



<script type="text/javascript">
    
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