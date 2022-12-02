package com.example.SECundum_WebshopServer;

import org.apache.http.HttpResponse;
import org.apache.http.HttpStatus;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpUriRequest;
import org.apache.http.impl.client.HttpClientBuilder;
import org.junit.Before;
import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.web.client.RestTemplate;

import java.io.IOException;

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

}
