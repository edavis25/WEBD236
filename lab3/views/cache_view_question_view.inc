<!DOCTYPE html>
<html>
	<head>
		<link rel="stylesheet" href="/Aptana/lab2/lab3/css/style.css" />
		
		<title><?php echo( $title ); ?></title>
	</head>
	<body>
		<div id="content-wrapper">


<h1><?php echo($question['Title']); ?></h1>
<hr />
<p>Posted on: <?php echo($question['Date']); ?></p>
<p>Tags: <?php echo( ($question['Tags']) ? $question['Tags'] : "<i>none</i>" ); ?></p>
<p class="question-content"><?php echo( nl2br($question['Content']) ); ?></p>

<a href="/Aptana/lab2/lab3/questions/edit_question/<?php echo( $question['QuestionID'] ); ?>">[Edit]</a>
<a href="#" onclick="toggle('confirm-delete')">[Delete]</a>
<div id="confirm-delete" style="display: none;">Are you sure? <a href="/Aptana/lab2/lab3/questions/delete_question/<?php echo( $question['QuestionID'] ); ?>">yes</a> / <a href="#" onclick="toggle('confirm-delete')">no</a></div>
<br /><br />
<a href="/Aptana/lab2/lab3/index">&lt;&lt; Back</a>

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

	
	</div> <!-- End content wrapper -->
	<footer>
		&copy; Eric Davis
	</footer>
</body>
</html>
