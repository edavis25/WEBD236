%% views/header.inc %%

<h1> {{ $title }}</h1>
<h3>{{ $subtitle }}</h3>

<!-- outer row loop -->
<?php foreach ($data as $question): ?>
    <div class="question">
        <a href="@@questions/view_question/{{$question->getId()}}@@"> {{ $question->getTitle() }}</a>
        <br />
        Posted: {{ $question->getDate() }} by <a href="@@user/view_user/{{ $question->getUserId() }}@@">{{ $question->getAuthorName() }}</a>
        <br />
        {{ ($question->getTags()) ? "Tags: " . $question->getTags() : '' }}
        <p class="question-content"> {{ substr($question->getContent(), 0, 240).".." }}</p>
    </div>
<?php endforeach ?>

<br />

[[ if (isLoggedIn()) : ]]
    <a href="@@questions/post_question/@@">[Post new question]</a>
[[ endif; ]]

%% views/footer.inc %%