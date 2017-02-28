<!DOCTYPE html>
<html>
	<head>
		<link rel="stylesheet" href="/lab/lab2/css/style.css" />
		
		<title><?php echo( $title ); ?></title>
	</head>
	<body>
		<div id="content-wrapper">


<h1><?php echo( $title ); ?></h1>
<div id="errors">
	<?php echo( isset($errors) ? $errors."<br />" : '' ); ?>
</div>
<form action="/lab/lab2/questions/edit_question" method="post">
	<label for="title">Title</label>
	<br />
	<input type="text" id="title" name="title" class="full-width" value= "<?php echo( isset($inputs['Title']) ? $inputs['Title'] : '' ); ?>" />
	<br />
	<label for="content-textarea">Content</label>
	<br />
	<textarea name="content" id="content-textarea" rows="15" class="full-width"><?php echo( isset($inputs['Content']) ? $inputs['Content'] : '' ); ?></textarea>
	<br />
	<label for="tags">Tags</label>
	<input type="text" id="tags" name="tags" class="full-width" value="<?php echo( isset($inputs['Tags']) ? $inputs['Tags'] : '' ); ?>" />
	<br /><br />
	<input type="hidden" name="id" value="<?php echo( $inputs['QuestionID'] ); ?>" />
	<input type="submit" value="Save Changes" id="submit-question" />
</form>
<br /><br />
<a href="/lab/lab2/index">&lt;&lt; Back</a>

	
	</div> <!-- End content wrapper -->
	<footer>
		&copy; Eric Davis
	</footer>
</body>
</html>