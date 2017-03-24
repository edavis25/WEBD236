%% views/header.inc %%

<h1>{{ $title }}</h1>
<hr />
<p>Posted on: {{$question->getDate()}} by <a href="@@user/view_user/{{ $question->getUserId() }}@@">{{ $question->getAuthorName() }}</a></p>

%% views/tags_view.inc %%

<p class="question-content">{{ nl2br($question->getContent()) }}</p>

<!-- Add edit/delete links if user is question author -->
[[ if ($isAuthor) : ]]
<a href="@@questions/edit_question/{{ $question->getId() }}@@">[Edit]</a>
<a href="#" onclick="toggle('confirm-delete')">[Delete]</a>
<div id="confirm-delete" style="display: none;">Are you sure? <a href="@@questions/delete_question/{{ $question->getId() }}@@">yes</a> / <a href="#" onclick="toggle('confirm-delete')">no</a></div>
[[ endif; ]]

<br /><br />
<a href="@@index@@">&lt;&lt; Back</a>

%% views/footer.inc %%
