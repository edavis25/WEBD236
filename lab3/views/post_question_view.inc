%% views/header.inc %%

<h1>{{ $title }}</h1>
<div id="errors">
	{{ isset($errors) ? $errors."<br />" : '' }}
</div>
<form action="@@questions/add_question@@" method="post">
	<label for="title">Title</label>
	<br />
	<input type="text" id="title" name="title" class="full-width" value= "{{ isset($inputs['title']) ? $inputs['title'] : '' }}" />
	<br />
	<label for="content-textarea">Content</label>
	<br />
	<textarea name="content" id="content-textarea" rows="15" class="full-width">{{ isset($inputs['content']) ? $inputs['content'] : '' }}</textarea>
	<br />
	<label for="tags">Tags</label>
	<input type="text" id="tags" name="tags" class="full-width" value="{{ isset($inputs['tags']) ? $inputs['tags'] : '' }}" />
	<br />
	<br />
	<input type="submit" value="Post Question" id="submit-question" />
</form>
<br />
<a href="@@index@@">&lt;&lt; Back</a>

%% views/footer.inc %%