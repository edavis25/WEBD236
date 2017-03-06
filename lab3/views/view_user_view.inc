%% views/header.inc %%

<h1>{{ $title }}</h1>

<table>
	<tr>
		<td>First Name: </td>
		<td>{{ $data['FirstName'] }}</td>
	</tr>
	<tr>
		<td>Last Name: </td>
		<td>{{ $data['LastName'] }}</td>
	</tr>
	<tr>
		<td>E-mail: </td>
		<td>{{ $data['Email'] }}</td>
	</tr>
</table>

<br />

[[ if ($ownsAccount) : ]]
<a href="@@user/edit_user@@">[Edit]</a>
<a href="#" onclick="toggle('confirm-delete')">[Delete]</a>
<div id="confirm-delete" style="display: none;">Are you sure? <a href="@@user/delete_user@@">yes</a> / <a href="#" onclick="toggle('confirm-delete')">no</a></div>
[[ endif; ]]

<h2>Questions By {{$data['FirstName'] ." ". $data['LastName']}}</h2>

[[ foreach ($questions as $row): ]]
	<div class="question">
		<a href="@@questions/view_question/{{$row['QuestionID']}}@@"> {{ $row['Title'] }}</a>
		<br />
		Posted: {{ $row['Date'] }} by <a href="@@user/view_user/{{ $row['UserID'] }}@@">{{ $data['FirstName'] ." ". $data['LastName'] }}</a>
		<br />
		{{ ($row['Tags']) ? "Tags: " . $row['Tags'] : '' }}
		<p class="question-content"> {{ substr($row['Content'], 0, 240).".." }}</p>
	</div>
[[ endforeach ]]

%% views/footer.inc %%