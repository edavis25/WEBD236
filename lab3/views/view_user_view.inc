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

%% views/footer.inc %%