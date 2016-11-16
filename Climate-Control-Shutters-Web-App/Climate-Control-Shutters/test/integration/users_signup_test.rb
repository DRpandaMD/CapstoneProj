require 'test_helper'

class UsersSignupTest < ActionDispatch::IntegrationTest
  #start testing for User Sign up
   test "invalid signup information " do
   	get signup_path
   	assert_no_difference 'User.count', 1 do 
   		post_via redirect users_path, user: {name: "Example User",
   								                         email: "user@example.com",
   								                         password: 				      "foo",
   								                         password_confirmation: "bar" }
   	end
   	assert_template 'users/new'
  end

end
