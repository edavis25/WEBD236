<?php include_once 'include/util.inc' ?>

%% views/header.inc %%

<?php include_once 'views/navigation.inc' ?>

<h1><?php echo (isLoggedIn()) ? 'LOGGED IN' : 'LOGGED OUT'; ?></h1>
<h2><?php echo ($id) ? "ID: $id" : '' ?></h2>

<h1> {{ $title }}</h1>
<h3>{{ $subtitle }}</h3>

<!-- outer row loop -->
<?php foreach ($data as $row): ?>
	<div class="question">
		<a href="@@questions/view_question/{{$row['QuestionID']}}@@"> {{ $row['Title'] }}</a>
		<br />
		Posted: {{ $row['Date'] }}
		<br />
		{{ ($row['Tags']) ? "Tags: " . $row['Tags'] : '' }}
		<p class="question-content"> {{ substr($row['Content'], 0, 240).".." }}</p>
	</div>
<?php endforeach ?>


<!-- <a href="@@questions/view_question/{{$record['id']}}@@">[View]</a -->
<br />
<a href="@@questions/post_question/@@">[Post new question]</a>

%% views/footer.inc %%