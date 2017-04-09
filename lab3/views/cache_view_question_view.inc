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
                        <?php  if (Authenticator::instance() -> can('admin_page')) : ?>
                        <li><a href="/lab/lab3/admin">Administrator</a></li>
                        <?php  endif; ?>
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
<hr />
<p>Posted on: <?php echo($question->getDate()); ?> by <a href="/lab/lab3/user/view_user/<?php echo( $question->getUserId() ); ?>"><?php echo( User::getFullName($question->getUserId()) ); ?></a></p>

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

<p class="question-content"><?php echo( markdown(html_entity_decode($question->getContent())) ); ?></p>

<!-- Add edit/delete links if user is question author -->
<?php  if ( $isAuthor || Authenticator::instance() -> can('question_edit')) : ?>
    <a href="/lab/lab3/questions/edit_question/<?php echo( $question->getId() ); ?>">[ Edit ]</a>
    <div class="delete-wrapper">
        <a href="##" class="delete-button">[ Delete ]</a>&nbsp;
        <div class="confirm-delete" style="display: none;"> 
            <a href="/lab/lab3/questions/delete_question/<?php echo( $question->getId() ); ?>"> yes</a> / <a href="##" class="delete-button">no</a>
        </div>
    </div>
    <br /><br /><hr /><br />
    <div id='file-upload'>
        <form action="/lab/lab3/file/add" method="post" enctype="multipart/form-data">
            <input type="hidden" name="question-id" value="<?php echo($question->getId()); ?>" />
            <label for="file">Add an attachment file:</label><hr />
            <input type="file" name="file" /><br />
            <div class="center">
                <input class="float-right" type="submit" value="Upload" />
            </div>
        </form>
    </div>
    <br /><br />
<?php  endif; ?>

<?php  if ($files && count($files) > 0) : ?>
<div id="attachments">
    <label><b>Attachments:</b></label>
    <ul>
    <?php  foreach ($files as $file) : ?>
        <li>
            <a href="/lab/lab3/file/view/<?php echo($file->getId()); ?>">[ View ]</a>
            <a href="/lab/lab3/file/download/<?php echo($file->getId()); ?>">[ Download ]</a>
            <?php  if ( $isAuthor || Authenticator::instance() -> can('question_edit')) : ?>
                <div class="delete-wrapper">
                    <a href="##" class="delete-button">[ Delete ]</a>&nbsp;
                    <div class="confirm-delete" style="display: none;">
                        <a href="/lab/lab3/file/delete/<?php echo($file->getId()); ?>/<?php echo($question->getId()); ?>"> yes</a> / <a href="##" class="delete-button">no</a>
                    </div>
                </div>
            <?php  endif; ?>
            &nbsp;<?php echo($file->getOrigName()); ?>
        </li>
    <?php  endforeach; ?>
    </ul>
</div>
<?php  endif; ?>
<!-- Comment to fix renderTemplate include bug -->
<div id="errors">
    <?php  if (isset($errors) && count($errors) > 0) : ?>
        <ul>
            <?php  foreach($errors as $error) : ?>
                <li><?php echo( $error ); ?></li>
            <?php  endforeach; ?>
        </ul>
    <?php  endif; ?>
</div>

<br />
<?php  if (Authenticator::instance() -> can('answer_create')) : ?>
    <div class="answer-form">
    Add an answer
    <form method="POST" action="/lab/lab3/answers/add_answer">
        <textarea name="answer-content" class="answer-textarea" rows="3"></textarea>
        <br />
        <input type="hidden" name="question-id" value="<?php echo( $question->getId() ); ?>" />
        <input type="submit" class="answer-submit" value="Post Answer" name="answer-button" />
    </form>

</div>
<?php  endif; ?>

<?php  if ($answers && count($answers) > 0) : ?>
    <h2>Answers:</h2>
    <?php  foreach($answers as $answer) : ?>
        <div class="answer">
            Posted <?php echo( $answer->getDate() ); ?> by 
            <a href="/lab/lab3/user/view_user/<?php echo( $answer->getUserId() ); ?>"><?php echo( User::getFullName($answer->getUserId()) ); ?></a>
    
            <div class="answer-content">
                <?php echo( nl2br($answer->getContent()) ); ?>
            </div>
    
            <?php  if ( (isLoggedIn() && $_SESSION['UserID'] == $answer->getUserId()) || Authenticator::instance() -> can('answer_delete')) : ?>
                <div class="delete-wrapper">
                    <a href="##" class="delete-button">[ Delete ]</a>&nbsp;
                    <div class="confirm-delete" style="display: none;"> 
                        <a href="/lab/lab3/answers/delete_answer/<?php echo( $answer->getId() ); ?>"> yes</a> / <a href="##" class="delete-button">no</a>
                    </div>
                </div>
            <?php  endif; ?>
            
        </div> <!-- End answer div -->
    <?php  endforeach; ?> 
<?php  endif; ?>
<!-- Comment to fix renderTemplate include bug -->
	
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


