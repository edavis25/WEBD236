%% views/header.inc %%
<h1>{{ $title }}</h1>
<form>
	<label for="title">Title</label>
	<br />
	<input type="text" id="title" name="title" class="full-width" required/>
	<br />
	<label for="content-textarea">Content</label>
	<br />
	<textarea name="textarea" id="content-textarea" rows="15" class="full-width" required></textarea>
	<br />
	<label for="tags">Tags</label>
	<input type="text" id="tags" name="tags" class="full-width" required />
	<br />
	<br />
	<input type="submit" value="Post Question" id="submit-question" />
</form>
<br />
<br />
<a href="@@index@@">&lt;&lt; Back</a>