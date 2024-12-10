from calculator import Calculator
from services.clickhouse import Clickhouse

from conftest import NewYearService, MockService, sample_config, \
                     sample_registered_services, sample_params, not_full_config, empty_config  


def test_calculator_initialization(sample_config, sample_registered_services, sample_params):
    calculator = Calculator(sample_config, sample_registered_services, sample_params)
    print(calculator._services)
    assert "kafka" in calculator._services
    assert "newyearservice" in calculator._services
    assert calculator._params == sample_params


def test_register_service(sample_config, sample_params):
    calculator = Calculator(sample_config, {}, sample_params)
    service = Clickhouse()
    calculator.register_service("clickhouse", service)
    assert "clickhouse" in calculator._services
    assert calculator._services["clickhouse"] == service



    

# def test_update_all_configs(sample_config, sample_registered_services, sample_params):
#     calculator = Calculator(sample_config, sample_registered_services, sample_params)
#     calculator.update_all_configs()
#     for service in calculator._services.values():
#         assert service.get_config() == sample_params


# def test_get_all_configs(sample_config, sample_services, sample_params):
#     # Проверка работы get_all_configs
#     calculator = Calculator(sample_config, sample_services, sample_params)
#     expected_config = {
#         "service1": sample_params,
#         "service2": sample_params,
#     }
#     # Добавляем отсутствующий сервис из конфигурации
#     calculator._config["service3"] = {"param3": 30}
#     all_configs = calculator.get_all_configs()
#     assert all_configs["service1"] == sample_params
#     assert all_configs["service2"] == sample_params
#     assert all_configs["service3"] == {"param3": 30}



def test_empty_config(empty_config, sample_registered_services, sample_params):
    calculator = Calculator(empty_config, sample_registered_services, sample_params)
    assert len(calculator._services) == 0
    assert calculator.get_all_configs() == {}


def test_not_full_config(not_full_config, sample_registered_services, sample_params):
    calculator = Calculator(not_full_config, sample_registered_services, sample_params)
    assert "kafka" in calculator._services
    assert "clickhouse" in calculator._services
    assert "scanner" in calculator._services
    assert calculator.get_all_configs() == {
                                            "kafka": {
                                                "replicas": 3,
                                                "memory": 7.5,
                                                "cpu": 0.438768,
                                                "storage": 0.3251
                                            },
                                            "clickhouse": {
                                                "replicas": 1,
                                                "memory": 16.0,
                                                "cpu": 1,
                                                "storage": 0.6380140000000001
                                            },
                                            "scanner": {
                                                "replicas": 1,
                                                "memory": 300,
                                                "cpu": 1,
                                                "storage": 0.601
                                            }
                                        }