package com.example.SECundum_WebshopServer;

import org.apache.http.HttpResponse;
import org.apache.http.HttpStatus;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.client.methods.HttpUriRequest;
import org.apache.http.impl.client.HttpClientBuilder;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;
import org.junit.Before;
import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.web.client.RestTemplate;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.equalTo;

@SpringBootTest
class SeCundumWebshopServerApplicationTests {

	private static RestTemplate restTemplate;

	private String baseUrl = "http://localhost:8080";


	@Before
	public static void init(){
		restTemplate = new RestTemplate();
	}

	@Test
	public void testGetAllCaffs() throws IOException {
		HttpUriRequest request = new HttpGet(baseUrl + "/caff/getAll");

		HttpResponse httpResponse = HttpClientBuilder.create().build().execute(request);

		assertThat(
				httpResponse.getStatusLine().getStatusCode(),
				equalTo(HttpStatus.SC_OK)
		);
	}

	@Test
	public void testGetCaff() throws IOException {
		HttpUriRequest request = new HttpPost(baseUrl + "/caff/get?name=Beautiful_scenery");

		HttpResponse httpResponse = HttpClientBuilder.create().build().execute(request);

		assertThat(
				httpResponse.getStatusLine().getStatusCode(),
				equalTo(HttpStatus.SC_METHOD_NOT_ALLOWED)
		);
	}

	@Test
	public void testValidLogin() throws IOException{
		URL obj = new URL(baseUrl+"/user/login");
		HttpURLConnection con = (HttpURLConnection) obj.openConnection();
		con.setRequestMethod("POST");
		con.setRequestProperty("Content-Type", "application/json");
		con.setRequestProperty("Accept", "application/json");
		con.setDoOutput(true);
		String jsonInputString = "{\"username\": \"lajos\", \"password\": \"martin1234\"}";
		try(OutputStream os = con.getOutputStream()) {
			byte[] input = jsonInputString.getBytes("utf-8");
			os.write(input, 0, input.length);
		}

		assertThat(
				con.getResponseCode(),
				equalTo(HttpStatus.SC_OK)
		);
	}

	@Test
	public void testInvalidLogin() throws IOException{
		URL obj = new URL(baseUrl+"/user/login");
		HttpURLConnection con = (HttpURLConnection) obj.openConnection();
		con.setRequestMethod("POST");
		con.setRequestProperty("Content-Type", "application/json");
		con.setRequestProperty("Accept", "application/json");
		con.setDoOutput(true);
		String jsonInputString = "{\"username\": \"lajos\", \"password\": \"invalidpw\"}";
		try(OutputStream os = con.getOutputStream()) {
			byte[] input = jsonInputString.getBytes("utf-8");
			os.write(input, 0, input.length);
		}

		assertThat(
				con.getResponseCode(),
				equalTo(HttpStatus.SC_INTERNAL_SERVER_ERROR)
		);
	}

	@Test
	public void testAddCommentAsUnauthorized() throws IOException{
		URL obj = new URL(baseUrl+"/comment/save");
		HttpURLConnection con = (HttpURLConnection) obj.openConnection();
		con.setRequestMethod("POST");
		con.setRequestProperty("Content-Type", "application/json");
		con.setRequestProperty("Accept", "application/json");
		con.setDoOutput(true);
		String jsonInputString = "{\"caff_name\": \"Beautiful scenery\", \"comment\": \"nice picture\"}";
		try(OutputStream os = con.getOutputStream()) {
			byte[] input = jsonInputString.getBytes("utf-8");
			os.write(input, 0, input.length);
		}

		assertThat(
				con.getResponseCode(),
				equalTo(HttpStatus.SC_UNAUTHORIZED)
		);
	}

	@Test
	public void testAddCommentAsAuthorized() throws IOException{
		URL obj = new URL(baseUrl+"/comment/save");
		HttpURLConnection con = (HttpURLConnection) obj.openConnection();
		con.setRequestMethod("POST");
		con.setRequestProperty("Content-Type", "application/json");
		con.setRequestProperty("Accept", "application/json");
		con.setRequestProperty("Authorization", "eyJhbGciOiJIUzUxMiJ9.eyJzdWIiOiJsYWpvcyIsImV4cCI6MTY3MDA4NTg2NCwiaWF0IjoxNjcwMDY3ODY0fQ.6_PNzXqReC-3sT3oVCBbMo0q3HhcVBNQxze1GhaObXFHVRqFbxkw-dqw2CRmmzO-tqJQW1m9cPv01a_SXL3b-A");
		con.setDoOutput(true);
		String jsonInputString = "{\"caff_name\": \"Beautiful scenery\", \"comment\": \"nice picture\"}";
		try(OutputStream os = con.getOutputStream()) {
			byte[] input = jsonInputString.getBytes("utf-8");
			os.write(input, 0, input.length);
		}

		assertThat(
				con.getResponseCode(),
				equalTo(HttpStatus.SC_OK)
		);
	}

	@Test
	public void testGetCommentsForCaff() throws IOException{
		URL obj = new URL(baseUrl+"/comment/getAll?caffName=Beautiful_scenery");
		HttpURLConnection con = (HttpURLConnection) obj.openConnection();
		con.setRequestMethod("GET");
		con.setRequestProperty("Content-Type", "application/json");
		con.setRequestProperty("Accept", "application/json");
		con.setDoOutput(true);

		assertThat(
				con.getResponseCode(),
				equalTo(HttpStatus.SC_OK)
		);
	}

	@Test
	public void testDeleteCommentWithUserRole() throws IOException{
		URL obj = new URL(baseUrl+"/user/login");
		HttpURLConnection con = (HttpURLConnection) obj.openConnection();
		con.setRequestMethod("POST");
		con.setRequestProperty("Content-Type", "application/json");
		con.setRequestProperty("Accept", "application/json");
		con.setDoOutput(true);
		String jsonInputString = "{\"username\": \"lajos\", \"password\": \"martin1234\"}";
		try(OutputStream os = con.getOutputStream()) {
			byte[] input = jsonInputString.getBytes("utf-8");
			os.write(input, 0, input.length);
		}

		JSONObject json = null;

		try(BufferedReader br = new BufferedReader(
				new InputStreamReader(con.getInputStream(), "utf-8"))) {
			StringBuilder response = new StringBuilder();
			String responseLine = null;
			while ((responseLine = br.readLine()) != null) {
				response.append(responseLine.trim());
			}
			JSONParser parser = new JSONParser();
			json = (JSONObject) parser.parse(String.valueOf(response));
		} catch (ParseException e) {
			e.printStackTrace();
		}



		obj = new URL(baseUrl+"/comment/delete?id=1");
		con = (HttpURLConnection) obj.openConnection();
		con.setRequestMethod("DELETE");
		con.setRequestProperty("Content-Type", "application/json");
		con.setRequestProperty("Accept", "application/json");
		con.setRequestProperty("Authorization", (String) json.get("token"));
		assertThat(
				con.getResponseCode(),
				equalTo(HttpStatus.SC_FORBIDDEN)
		);
	}


	@Test
	public void testDeleteCommentWithAdminRole() throws IOException{
		URL obj = new URL(baseUrl+"/user/login");
		HttpURLConnection con = (HttpURLConnection) obj.openConnection();
		con.setRequestMethod("POST");
		con.setRequestProperty("Content-Type", "application/json");
		con.setRequestProperty("Accept", "application/json");
		con.setDoOutput(true);
		String jsonInputString = "{\"username\": \"keve98\", \"password\": \"keve1234\"}";
		try(OutputStream os = con.getOutputStream()) {
			byte[] input = jsonInputString.getBytes("utf-8");
			os.write(input, 0, input.length);
		}

		JSONObject json = null;

		try(BufferedReader br = new BufferedReader(
				new InputStreamReader(con.getInputStream(), "utf-8"))) {
			StringBuilder response = new StringBuilder();
			String responseLine = null;
			while ((responseLine = br.readLine()) != null) {
				response.append(responseLine.trim());
			}
			JSONParser parser = new JSONParser();
			json = (JSONObject) parser.parse(String.valueOf(response));
		} catch (ParseException e) {
			e.printStackTrace();
		}


		obj = new URL(baseUrl+"/comment/delete?id=1");
		con = (HttpURLConnection) obj.openConnection();
		con.setRequestMethod("DELETE");
		con.setRequestProperty("Content-Type", "application/json");
		con.setRequestProperty("Accept", "application/json");
		con.setRequestProperty("Authorization", (String) json.get("token"));
		assertThat(
				con.getResponseCode(),
				equalTo(HttpStatus.SC_OK)
		);
	}

	@Test
	public void testDownloadCaffUnauthorized() throws IOException {
		URL obj = new URL(baseUrl+"/caff/download?name=Beautiful_scenery");
		HttpURLConnection con = (HttpURLConnection) obj.openConnection();
		con.setRequestMethod("GET");
		con.setRequestProperty("Content-Type", "application/json");
		con.setRequestProperty("Accept", "application/json");

		assertThat(
				con.getResponseCode(),
				equalTo(HttpStatus.SC_UNAUTHORIZED)
		);
	}

	@Test
	public void testDownloadCaffAuthorized() throws IOException {
		URL obj = new URL(baseUrl+"/user/login");
		HttpURLConnection con = (HttpURLConnection) obj.openConnection();
		con.setRequestMethod("POST");
		con.setRequestProperty("Content-Type", "application/json");
		con.setRequestProperty("Accept", "application/json");
		con.setDoOutput(true);
		String jsonInputString = "{\"username\": \"lajos\", \"password\": \"martin1234\"}";
		try(OutputStream os = con.getOutputStream()) {
			byte[] input = jsonInputString.getBytes("utf-8");
			os.write(input, 0, input.length);
		}

		JSONObject json = null;

		try(BufferedReader br = new BufferedReader(
				new InputStreamReader(con.getInputStream(), "utf-8"))) {
			StringBuilder response = new StringBuilder();
			String responseLine = null;
			while ((responseLine = br.readLine()) != null) {
				response.append(responseLine.trim());
			}
			JSONParser parser = new JSONParser();
			json = (JSONObject) parser.parse(String.valueOf(response));
		} catch (ParseException e) {
			e.printStackTrace();
		}


		obj = new URL(baseUrl+"/caff/download?name=Beautiful_scenery");
		con = (HttpURLConnection) obj.openConnection();
		con.setRequestMethod("POST");
		con.setRequestProperty("Content-Type", "application/json");
		con.setRequestProperty("Accept", "application/json");
		con.setRequestProperty("Authorization", (String) json.get("token"));
		assertThat(
				con.getResponseCode(),
				equalTo(HttpStatus.SC_OK)
		);
	}

}
