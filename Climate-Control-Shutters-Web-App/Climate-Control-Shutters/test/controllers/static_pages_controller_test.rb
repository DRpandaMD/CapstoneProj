require 'test_helper'

class StaticPagesControllerTest < ActionDispatch::IntegrationTest
  test "should get home" do
    get root_path
    assert_response :success
    assert_select "title", "Climate Control Shutters Web App"
  end

  test "should get help" do
    get	help_path
    assert_response :success
    assert_select "title", "Help | Climate Control Shutters Web App"
  end

  test "should get about" do
  	get about_path
  	assert_response :success
  	assert_select "title", "About | Climate Control Shutters Web App"
  end

  test "should get contact" do
  	get contact_path
  	assert_response :success
  	assert_select "title", "Contact | Climate Control Shutters Web App"
  end
end
