require 'test_helper'

class DatasControllerTest < ActionDispatch::IntegrationTest
  test "should get new" do
    get datas_new_url
    assert_response :success
  end

end
