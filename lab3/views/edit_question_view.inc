%% views/header.inc %%

<h1>{{ $title }}</h1>

%% views/errors.inc %%

<form action="@@questions/edit_question@@" method="post">
	<label for="title">Title</label>
	<br />
        <input type="text" id="title" name="title" class="full-width" value= "{{ $question->getTitle() }}" />
	<br />
	<label for="content-textarea">Content</label>
	<br />
        <textarea name="content" id="content-textarea" rows="15" class="full-width">{{ $question->getContent() }}</textarea>
	<br />
	<label for="tags">Tags</label>
        <input type="text" id="tags" name="tags" class="full-width" value="{{ $question->getTags() }}" />
	<br /><br />
        <input type="hidden" name="id" value="{{ $question->getId() }}" />
	<input type="submit" value="Save Changes" id="submit-question" />
</form>
<br /><br />
<a href="@@index@@">&lt;&lt; Back</a>

%% views/footer.inc %%