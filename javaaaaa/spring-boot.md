# spring

<http://docs.spring.io/spring/docs/current/spring-framework-reference/htmlsingle>

## Ads ranking

rank score = quality score * bid
 ||||
 |:----:|:----:|:----: |
| click count & impression |  pClick & Relevance Score| bid & CPC(Cost per click) |

```python
# e.g: {"count":1, "adid_terms": "12333_optical"}
import json 
import sys
import pyspark 
import SparkContext 
def get_terms(line):
    entry = line.split('_')
    return entry[1]

def get_adid_terms(line):
    entry = json.loads(line.strip())
    ad_id = entry['adId']
    adid_terms = []
    for term in entry['keyWords']:
        val = str(ad_id) + "_" + term
        adid_term.append(val)
    return adid_terms

def generate_json(items):
    result = {}
    result['doc_freq'] = items[0]
    result['count'] = items[1]
    return jons.dumps(result)

if __name__ == "__main__":
    adfile = sys.argv[1]
    sc = SparkContext(appName ="DF_Feature")
    data = sc.textFile(adfile).flatMap(lambda line: get_adid_terms(line)).
    distinct().map(lambda w:(get_term(w), 1)).reduceByKey(lambda v1,v2: v1+v2).
    map(generate_json)
    data.saveAsTextFile("/log/DF")
    sc.stop()
```

**TF*IDF** - measures the relative importance of a term in a given piece of text
**Term Frequency & Inverse Document Frequency**

- how often term, e.g "dog", occur in the article
- the **document frequency** measures how many docs a term appears in. **inverse document frequency(1/df)**
then measures how **special** the term is.

## rabbitmq

ConnectionFactory-> connection-> channel

## crawler

503 --- service unavailable  5xx Server Error

## spring boot

spring framework
spring web mvc
auto configurations

- Delete api **question&**
/fooddelivery.com/restaurants/{restaurantname}/deleteMenu
/fooddelivery.com/restaurants/deleteByRestaurantname/{restaurantname}
/users/deleteUser/{userId}

## philosophy

Provide choice at every level
Maintain strong backward compatibility
Care about API design
Set high standards for code quality

## 项目结构粗粒度理解

domain - 定义所有的变量 jpa相关的Repository
service - 实现所有的microservice
rest - http交互

configuration model and a dependency injection mechanism

## WEBSOCKET

## @Embeddable VS @Entity

**dependent vs independent**

- **oo relation**
a dependent object is considered an aggregate or composite association

- **relational model**  
dependent object could have its own table
data could be embedded in the independent object's table
dependent data is included in the independent object's table .

- **embedded object**
cannot be directly persisted or queried can only be persisted
or queried in the context of the source object in which it is
embedded.
does not have  an id or table
e.g === address depends on user | user is independent on address
| address can be embedded in user | address is embeddable

---------------------------------------------------------------

- > CrudRepository  
**interafce for generic crud operations**

- > PagingAndSortingRepository
**Iterable<T> findAll Page<T> findAll(Pageable pageable)**

- > JpaRepository
**savaAndFlush deleteInBatch deleteAllInBatch**

---------------------------------------------------------------

**Answers**

--- all about design decision

```java
import javax.persistence.Entity/GeneratedValue/Id/ManyToOne;
import lombok.AllArgsConstructor;

@Entity
public class UserEntity{
    @Id
    @GeneratedValue
    private Long id;
    private String username;

    @Embedded
    private Address address;
}

@Embeddable
@AllArgsConstructor ---
public class Address {
    private String city;
}
```

## POM & **Fat jar**

@SpringBootApplication
@RestController
@RequestMapping(value="/{userId}", method=RequestMethod.GET)
@PathVariable int userId
@Data
@Requiredargconstructor
public class UnitInfo{

}

lombok.data
<parent>
<groupId>org.springframework.boot</groupId>
<artifactId>spring-boot-starter-parent<artifactId>
<version>1.3.0.RELEASE</version>
</parent>
spring-data-rest-hal-browser [org.springframework.data]
spring-boot-starter-web[dependency] | data-rest data-mongodb  data-jpa[dependency] | maven-plugin[build plugins]
com.h2database

<groupId>org.projectlombok</groupId>
<artifactId>lombok</artifactId>
